//
//  main.cpp
//  hw7.1
//
//  Created by Aliza Virji on 3/19/24.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <cctype>
#include <iterator>
#include <stack>
using namespace std;


// function to parse an HTML file and extract links to local files
std::list<std::string> extractLinksFromHTML(const std::string& fileContent) {
    std::list<std::string> links;
    // regular expression to match href attributes in anchor tags
    std::regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    std::smatch match;

    // search for links in the HTML content
    std::string::const_iterator start = fileContent.cbegin();
    while (std::regex_search(start, fileContent.cend(), match, linkRegex)) {
        if (match.size() > 1) {
            links.push_back(match[1].str());
        }
        start = match.suffix().first;
    }

    return links;
}

//function to extract the title from the page
string extractTitle(const string& page) {
    //opens page passed in
    ifstream fileStream(page);
    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        //finds the beginning and end of the title
        size_t startTitle = fileContent.find("<title>");
        size_t endTitle = fileContent.find("</title>");
        if (startTitle != std::string::npos && endTitle != std::string::npos) { //if something was found,
            startTitle += strlen("<title>"); // moves the start to the end of the opening tag
            return fileContent.substr(startTitle, endTitle - startTitle); //returns the substring of the title
        }
    }
    return "Nothing found";
}

//function to extract the URL, just returns the file name since that is the URL
string extractURL(const string& page) {
    return page;
}

//function to find the exact match of the word, returns if the exact query was found in the file content
string::size_type findExactMatch(const string& fileContent, const string& query) {
    std::string::size_type startPos = 0; // begins at start of the file content
    while (startPos < fileContent.length()) {
        std::string::size_type foundPos = fileContent.find(query, startPos);
        if (foundPos != std::string::npos) {
            //creates valid start position if the position is the start or the character before is not a letter or a number
            bool canStart = foundPos == 0 || !std::isalnum(fileContent[foundPos - 1]);

            // checks if the position is at the end or if the character after is not a letter or number
            bool canEnd = (foundPos + query.length() >= fileContent.length()) || !std::isalnum(fileContent[foundPos + query.length()]);

            //found the word by itself without any letter or number around it
            if (canStart && canEnd) {
                return foundPos;
            } else {
                //if it is not a valid instance of the word, moves it to the next letter after the word is found to look for the word in a different instance in the file content
                startPos = foundPos + 1;
            }
        } else {
            //if there is not a single instance of the word that passes the conditions above, breaks
            break;
        }
    }
    return string::npos; //returns npos if nothing can be found
}
//checks if the word is a whole match by seeing if there are letters/numbers before
bool isWholeWordMatch(const std::string& bodyContent, std::string::size_type pos, const std::string& word) {
    if (pos > 0 && std::isalnum(bodyContent[pos - 1])) {
        return false; // not a whole word match because character before is letter or number
    }
    
    if ((pos + word.length() < bodyContent.length()) && std::isalnum(bodyContent[pos + word.length()])) {
        return false; // not a whole word match due to another letter/number after the word
    }
     
    return true; //word matches, func returns true
}

//extract snippet function, takes out snippet from file
std::string extractSnippet(const std::string& page, const std::vector<std::string>& keywords, bool isPhraseSearch) {
    std::ifstream fileStream(page);
    if (!fileStream.is_open()) {
        return "ERROR: File cannot be opened";
    }
    //finds beginning and ending body
    std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
    std::string::size_type bodyStartPos = fileContent.find("<body");
    std::string::size_type bodyEndPos = fileContent.find("</body>");
    //makes a string out of this content
    std::string bodyContent = fileContent.substr(bodyStartPos, bodyEndPos - bodyStartPos);

    std::string::size_type startPos = std::string::npos;
    //does phrase search check first
    if (isPhraseSearch) {
        std::string phrase;
        for (size_t i = 0; i < keywords.size(); ++i) {
            if (!phrase.empty()) phrase += " "; //combines the words together to find the exact phrase
            phrase += keywords[i];
        }
        //puts into find exact match function to find where it is in file
        startPos = findExactMatch(bodyContent, phrase);
    } else { //case for non phrase search
        //combines words w space between
        string combinedkeywords;
        for (size_t i = 0; i < keywords.size(); ++i) {
            if (i > 0) combinedkeywords += " ";
            combinedkeywords += keywords[i];
        }
        //finds an exact match for the entire phrase together first
        startPos = findExactMatch(bodyContent, combinedkeywords);

        // if the concatenated phrase is not found, look only for the first occurrence of the first keyword
        if (startPos == std::string::npos && !keywords.empty()) {
            std::string::size_type foundPos = findExactMatch(bodyContent, keywords[0]);
            if (foundPos != std::string::npos && isWholeWordMatch(bodyContent, foundPos, keywords[0])) {
                startPos = bodyContent.rfind('.', foundPos) + 1;
            }
        }
    }
    //if starting position is found
    if (startPos != std::string::npos) {
        startPos = bodyContent.rfind('.', startPos) + 1; // starts from the beginning of the sentence before word found
        while (startPos < bodyContent.length() && std::isspace(bodyContent[startPos])) {
            ++startPos;
        }
        //makes the end of the substring 120 characters after the beginning part is found
        std::string::size_type endPos = std::min(startPos + 120, bodyContent.length());
        return bodyContent.substr(startPos, endPos - startPos); //returns this substring
        
    }
    return "Nothing found"; //otherwise returns this if no snippet found
}

//extracts the description
std::string extractDescription(const std::string& page) {
    ifstream fileStream(page);
    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        size_t startt = fileContent.find("<meta name=\"description\""); //makes this the start of where description found
        if (startt != std::string::npos) {
            size_t startPos = fileContent.find("content=\"", startt) + strlen("content=\""); //start of the actual description content
            if (startPos != std::string::npos) {
                //finds where the last quotation is and makes that the end of the substring
                size_t endPos = fileContent.find("\"", startPos);
                if (endPos != std::string::npos) { //if is found
                    return fileContent.substr(startPos, endPos - startPos); //returns the description substring
                }
            }
        }
    }
    return "Nothing found"; //otherwise returns this statement
}


set<string> parseFile(const string& fileContent) {
    set<string> wordsinFile;
    
    std::istringstream content(fileContent);
    string word;
    while (content >> word) {
        std::string word2;
        for (size_t i = 0; i < word.size(); ++i) {
            if (std::isalnum((word[i]))) {
                word2 += word[i];
            }
        }
        if (!word2.empty()) {
            wordsinFile.insert(word2);
        }
    }

    return wordsinFile;
}
//maps inverted index
void mapInvertedIndex(const set<string>& wordsinFile, const string& page, map<string, set<string>>& invertedIndex) {
    for (set<string>::const_iterator itr = wordsinFile.begin(); itr != wordsinFile.end(); ++itr) { //for each word in the file passed in
        invertedIndex[*itr].insert(page); //adds this document to the set of documents that is the value to the key word
    }
}
 
//simplifyPath function #1
string simplifyPath(string path) {
        std::string item;
        std::stack<string> myStack;
        // convert path to a string stream, and split it by the delimiter '/'.
        stringstream ss(path);
        while(getline(ss, item, '/')){
            if(item == ".."){
                if(!myStack.empty()){
                    myStack.pop();
                }
            }else if(item != "." && item != ""){
                // we only push valid items into the stack
                myStack.push(item);
            }
        }
        // since we were given an absolute path, which starts with a slash, if at this moment the stack is empty, it means either we didn't push anything into the stack, or everything is popped out.
        if(myStack.empty()){
            return "/";
        }
        std::string result = "";
        // now let's concatenate all valid items.
        while(!myStack.empty()){
            result = "/" + myStack.top() + result;
            myStack.pop();
        }
        return result;
    }

//simplifyPath2 function, cleaning up the file names for certain cases and finding the word in the format file_.html
string simplifyPath2(std::string page) {
    string item;
    string result; //string for the ending file after simplifying it

    //makes path a stringstream
    std::stringstream ss(page);

    // splits the path by '/'
    while (getline(ss, item, '/')) {
        if (!item.empty()) {
            result = item; // keep updating result variable with the non-empty segments that are found last
        }
    }
    // result is now the filename
    return result;
}

//webCrawler function, goes through each page and recursively finds each link each page contains, and continues to open these files until all the files have been opened, creates inverted index as it goes
void webCrawler(const string& seedURL, map<string, set<string>>& invertedIndex, set<string>& visitedPages) {
    if (seedURL.find("..") != string::npos) { //looks for the parent directory in each file, returns if found
        return;
    }
    
    if (visitedPages.find(seedURL) != visitedPages.end()) { //if the page has already been opened, return and do not look at it again
        return;
    }
    
    std::string directory;
    // suppose URL is "html_files/subdir1/subdir2/file7.html"
    size_t lastSlashPos = seedURL.find_last_of('/');
    if (lastSlashPos != std::string::npos) {
        // directory will now be "html_files/subdir1/subdir2/"
        directory = seedURL.substr(0, lastSlashPos + 1);
    }
    // adds page to visitedPages so it won't be looked at again
    visitedPages.insert(seedURL);
    
    // open and read the contents of the file
    ifstream fileStream(seedURL);

    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>()); //gets fileContent
        
        // extract links from extrackLinks function
        list<string> links = extractLinksFromHTML(fileContent);
        set<string> wordsinFile = parseFile(fileContent); //finds the set of all the words in the file
        // continues to map the inverted index with the set of words found from the file
        mapInvertedIndex(wordsinFile, seedURL, invertedIndex);
        fileStream.close();
        // recursively crawl through each link found in the current page from the links list
        for (list<string>::const_iterator linkIt = links.begin(); linkIt != links.end(); ++linkIt) {
            if (linkIt->find("../") != string::npos ) { //case in which ../ is found, then it has to simplify the path by removing part of the directory section and adding on the right part to it, so that it can be opened properly
                string stringg = simplifyPath(*linkIt);
                std::string modifiedURL = seedURL;
                size_t lastPos = modifiedURL.rfind('/');
                if (lastPos != std::string::npos) {
                    // finds the second to last '/' character so it can place the new file name in
                    size_t secondLastPos = modifiedURL.rfind('/', lastPos - 1);
                    if (secondLastPos != std::string::npos) {
                        // removes content from the last '/' to the end of the string
                        modifiedURL.erase(secondLastPos);
                        // concatenates the new string to the copy
                        modifiedURL += stringg;
                    }
                }
                //recursively calls webcrawler for the cases with the ../
                webCrawler(modifiedURL, invertedIndex, visitedPages);
            }
            //recursively calls webcrawler for the other cases
            webCrawler(directory+*linkIt, invertedIndex, visitedPages);
        }
    }
}

//function to count the number of occurances of a word in a string, used for determing keyword densities
int countWordOccurrences(const std::string& str, const std::string& word) {
    int count = 0;
    size_t pos = 0;

    // loops through the string passed in searching for the word
    while ((pos = str.find(word, pos)) != std::string::npos) {
        // accounts for symbols that are not letters or numbers before and after the word
        bool wordStart = (pos == 0) || !std::isalpha(str[pos - 1]);
        bool wordEnd = (pos + word.length() == str.length()) || !std::isalpha(str[pos + word.length()]);

        if (wordStart && wordEnd) {
            ++count;
        }

        // moves past the current finding of the word
        pos += word.length();
    }

    return count; //returns the count of the word
}

//calculates the page score with the keyword density and backlinks score determined
double calculatePageScore(double keywordDensity, double backlinksScore) {
    double pagescore;
    pagescore = (0.5 * keywordDensity + 0.5 * backlinksScore);
    return pagescore;
}

//calculates the density across all documents
vector<double> calculateDensityacrossAll(const vector<string>& key, set<string> value, double totalChar, set<string> allDocs) {
    vector<double> keywordDensityperWord; //
    map<string, double> docstoKDs;
        for (int i = 0; i < key.size(); ++i) {
            //goes through each key and finds the density
            double sum1 = 0;
            vector <int> DAADwords;
            vector <size_t> DAADtotal;
            //goes through every single doc
            for (set<string>::const_iterator setIt = allDocs.begin(); setIt != allDocs.end(); ++setIt) {
                ifstream fileStream(*setIt); //opens the doc
                size_t sizeofDoc;
                if (fileStream.is_open()) {
                    std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
                    sizeofDoc = fileContent.length(); //finds size of doc
                    DAADtotal.push_back(sizeofDoc);
                    int countofWord = countWordOccurrences(fileContent, key[i]); //uses countWordOccurances function to count how many times the word shows up in the documents
                    sum1 += countofWord;
                    DAADwords.push_back(countofWord); //pushes back the count of the word into a vector
                }
            }
            keywordDensityperWord.push_back(sum1/totalChar); //pushes back the keyword den of the word after dividing it by the total number of characters
        }
    return keywordDensityperWord; 
}

//function that calculates the keyword density per doc
double calculateKeywordDensity(const vector<string>& key, string value, vector<double>& DAADS) {
    double keywordDen=0; //keyword density that is returned for the word
    size_t sizeofDoc = 0;
    int countofWord = 0;
    //goes through each key word and calculates the keyword density across all docs that it is found in
    for (int i=0; i < key.size(); ++i) {
        double currentDAAD = DAADS[i];
        ifstream fileStream(value);
        if (fileStream.is_open()) {
            std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
            sizeofDoc = fileContent.length();
            countofWord = countWordOccurrences(fileContent, key[i]);
        }
        keywordDen += (countofWord/(sizeofDoc*currentDAAD)); //adds the density for each word to this
    }
    return keywordDen; //final number is the keyword density returned for all words in the vector in that document
}

// calculate the backlink score for the page passed in
double calculateBacklinkScore(const string& page, const map<string, set<string>>& docstoLinks, ofstream& outputFile) {
    double backlinksScore = 0.0;
    string page2 = simplifyPath2(page);
    // iterates through the docstoLinks to find backlinks to the target page, docstoLinks created in main
    for (map<string, set<string>>::const_iterator pageEntry = docstoLinks.begin(); pageEntry != docstoLinks.end(); ++pageEntry) {
        const string& currentPage = pageEntry->first;
        const set<string>& outgoingLinks = pageEntry->second;
        
        // checks if the current page is linked to the page passed in
        if (outgoingLinks.find(page2) != outgoingLinks.end()) {
            // continuously calculates the contribution from the current backlink no more links found
            double contribution = 1.0 / (1 + outgoingLinks.size());
            backlinksScore += contribution;
        }
    }
    return backlinksScore; //returns final backlinks score
}


int main(int argc, const char * argv[]) {
    string seedURL = argv[1];
    ifstream input(argv[2]);
    //initialiation of invertedIndex, visited links, links found
    map<string, set<string>> invertedIndex;
    set<string> visitedLinks;
    list<string> linksFound;
    webCrawler(seedURL, invertedIndex, visitedLinks); //initial call of webcrawler that opens all the docs and simultaneously builds the inverted index
    double totalChar = 0;
    
    set<string> allDocs; //set of all documents, used later in coe
    //goes through inverted index
    for (map<string, set<string>>::const_iterator mapIt = invertedIndex.begin(); mapIt != invertedIndex.end(); ++mapIt) {
        // goes through the set of documents in the inverted index
        for (set<string>::const_iterator setIt = mapIt->second.begin(); setIt != mapIt->second.end(); ++setIt) {
            allDocs.insert(*setIt); //inserts it into the set of all docs
        }
    }
    //calculations for the total nunber of characters
    for (set<string>::const_iterator allDocsitr = allDocs.begin(); allDocsitr != allDocs.end(); ++allDocsitr) {
        ifstream fileStream(*allDocsitr);
        if (fileStream.is_open()) {
            //cout << "open: ";
            std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
            totalChar += fileContent.length();
        }
    }
    
    //map of string keys and sets for values
    map<string, set<string>> docstoLinks;
    for (set<string>::const_iterator allDocsitr = allDocs.begin(); allDocsitr != allDocs.end(); ++allDocsitr) {
        ifstream fileStream(*allDocsitr); //opens each doc
        if (fileStream.is_open()) {
            std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
            list<string> links = extractLinksFromHTML(fileContent); //extracts the links
            set<string> linksSet; //set of the links
            
            for (list<string>::const_iterator linkItr = links.begin(); linkItr != links.end(); ++linkItr) {
                // apply simplifyPath2 to each link before adding it to the set
                string simplifiedLink = simplifyPath2(*linkItr);
                linksSet.insert(simplifiedLink); //adds each link to the set
            }
            
            //inserts the new set of links into the map
            docstoLinks[*allDocsitr] = linksSet; //adds the linksSet as a value to each doc key
        }
    }
    
    //code to conduct the regular search and phrase search
    string keyword;
    std::vector<string> allkeywords;
    int counter = 1; //counter to keep track of the output files 
    while (getline(input, keyword)) {
        bool phrasesearch = false;
        allkeywords.push_back(keyword);
        string output = "out" + to_string(counter) + ".txt"; //makes all the outut files
        ofstream outputFile(output);
        //code to see if the first and last characters are quotations, if they are, sets phrasesearch = true;
        size_t startPos = keyword.find('\"');
        if (startPos != std::string::npos) {
            // finds the position of the next quotation mark after the first
            size_t endPos = keyword.find('\"', startPos + 1);
            if (endPos != std::string::npos) {
                phrasesearch = true;
            }
        }
        //goes through the keyword and if there are quotes, extracts the phrase (only for phrase search)
        if (!keyword.empty()) {
            size_t startPos = keyword.find('\"');
            size_t endPos = string::npos;
            if (startPos != string::npos) {
                endPos = keyword.find('\"', startPos + 1);
            }
            bool phrasesearch = startPos != string::npos && endPos != string::npos;
            
            if (phrasesearch) {
                string phrase = keyword.substr(startPos + 1, endPos - startPos - 1);
                set<string> phraseContainingDocs;
                // iterates over all documents to find the ones containing the phrase
                for (set<string>::const_iterator docItr = allDocs.begin(); docItr != allDocs.end(); ++docItr) {
                    ifstream fileStream(*docItr);
                    if (fileStream.is_open()) {
                        string fileContent((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
                        if (fileContent.find(phrase) != string::npos) {
                            phraseContainingDocs.insert(*docItr);
                        }
                    }
                }
                
                // breaks the phrase into individual words
                vector<string> wordsInPhrase;
                stringstream ss(phrase);
                string word;
                //makes a vector of the words
                while (ss >> word) {
                    wordsInPhrase.push_back(word);
                }
                
                vector<tuple<string, double, string, string, string, string>> docComs; //makes a vector of tuples with all the different components that will be printed out
                outputFile << "Matching documents: " << endl << endl;
                //calculates density across all docs
                vector<double> DAADS = calculateDensityacrossAll(wordsInPhrase, phraseContainingDocs, totalChar, allDocs);
                for (set<string>::const_iterator docItr = phraseContainingDocs.begin(); docItr != phraseContainingDocs.end(); ++docItr) { //goes through each doc that has phrase and calculates keyword density, backlinks score, and overall page scores for each doc
                    double keywordPerDoc = calculateKeywordDensity(wordsInPhrase, *docItr, DAADS);
                    double backlinksScore = calculateBacklinkScore(*docItr, docstoLinks, outputFile);
                    double pagescore = calculatePageScore(keywordPerDoc, backlinksScore);
                    //then extracts title, URL, description, and snippet using the functions
                    string title = extractTitle(*docItr);
                    string URL = extractURL(*docItr);
                    string description = extractDescription(*docItr);
                    string snippet = extractSnippet(*docItr, wordsInPhrase, phrasesearch);
                    docComs.emplace_back(make_tuple(*docItr, pagescore, snippet, description, title, URL)); //code to place it into docInfo
                    sort(docComs.begin(), docComs.end(), [](const tuple<string, double, string, string, string, string>& a, const tuple<string, double, string, string, string, string>& b) {
                        return get<1>(a) > get<1>(b); // sorts the docs by the page score, which is the first component of the vector of tupes
                    });
                //code to output to output file
                }
                if (phraseContainingDocs.empty()) {
                    outputFile << "Your search - " << phrase << " - did not match any documents.";
                } else {
                    for (size_t i = 0; i < docComs.size(); ++i) {
                        const tuple<string, double, string, string, string, string>& doc = docComs[i];
                        outputFile << "Title: " << get<4>(doc) << endl;
                        outputFile << "URL: " << get<5>(doc) << endl;
                        outputFile << "Description: " << get<3>(doc) << endl;
                        outputFile << "Snippet: " << get<2>(doc);
                        if (i < docComs.size() - 1) {
                            outputFile << endl << endl; // adds an extra newline only if its not the last element being outputted
                        }
                    }
                }

            } else if (!phrasesearch) { //if phrasesearch = false;
                //does same thing, making a map of all the words to the docs
                map<vector<string>, set<string>> wordToIntDocs;
                vector<string> regvector; //vector of all the regular words
                stringstream read(keyword); //stringstreams the keyword to make it easy to push back to vector
                //pushes it back into vector
                string keyword2;
                while(read >> keyword2) {
                    regvector.push_back(keyword2);
                }
                //goes through inverted index and makes the common docs for the words in regvector
                set<string> commonDocs;
                if (!regvector.empty() && invertedIndex.find(regvector[0]) != invertedIndex.end()) {
                    commonDocs = invertedIndex[regvector[0]];
                }
                
                // figuring out the intersection of documents for all words in regvector
                for (size_t i = 0; i < regvector.size(); ++i) {
                    map<string, set<string>>::iterator it = invertedIndex.find(regvector[i]);
                    if (it != invertedIndex.end()) { //if the word is in the inverted index, proceed
                        set<string> intersection;
                        //goes through common docs and inserts the doc if the word is found in the doc
                        for (set<string>::iterator docIt = commonDocs.begin(); docIt != commonDocs.end(); ++docIt) {
                            if (it->second.find(*docIt) != it->second.end()) {
                                intersection.insert(*docIt);
                            }
                        }
                        //makes common docs = intersection
                        commonDocs = intersection;
                    } else {
                        commonDocs.clear(); // clear commonDocs if no words found
                        break;
                    }
                    // maps each word to common documents
                    
                    if (!commonDocs.empty()) {
                        wordToIntDocs[regvector] = commonDocs;
                    }
                    
                }
                //if common docs empty, outputs that the search was not found
                if (commonDocs.empty()) {
                    outputFile << "Your search - " << keyword << " - did not match any documents.";
                }
                //DOES SAME PROCESS AS PHRASE SEARCH HERE
                vector<tuple<string, double, string, string, string, string>> docComs;
                
                for (map<vector<string>, set<string>>::iterator mapIt = wordToIntDocs.begin(); mapIt != wordToIntDocs.end(); ++mapIt) {
                    
                    vector<double> DAADS = calculateDensityacrossAll(mapIt->first, mapIt->second, totalChar, allDocs);
                    for (set<string>::const_iterator setIt = mapIt->second.begin(); setIt != mapIt->second.end(); ++setIt) {
                        double keyWordperDoc = calculateKeywordDensity(mapIt->first, *setIt, DAADS);
                        double backlinksScore = calculateBacklinkScore(*setIt, docstoLinks, outputFile);
                        double pagescore = calculatePageScore(keyWordperDoc, backlinksScore);
                        string title = extractTitle(*setIt);
                        string URL = extractURL(*setIt);
                        string description = extractDescription(*setIt);
                        string snippet = extractSnippet(*setIt, regvector, phrasesearch);
                        docComs.emplace_back(make_tuple(*setIt, pagescore, snippet, description, title, URL));
                        sort(docComs.begin(), docComs.end(), [](const tuple<string, double, string, string, string, string>& a, const tuple<string, double, string, string, string, string>& b) {
                            return get<1>(a) > get<1>(b);
                        });
                        
                        
                    }
                    if (!commonDocs.empty()) {
                        outputFile << "Matching documents: " << endl << endl;
                        for (size_t i = 0; i < docComs.size(); ++i) {
                            const tuple<string, double, string, string, string, string>& doc = docComs[i];
                            outputFile << "Title: " << get<4>(doc) << endl;
                            outputFile << "URL: " << get<5>(doc) << endl;
                            outputFile << "Description: " << get<3>(doc) << endl;
                            outputFile << "Snippet: " << get<2>(doc);
                            if (i < docComs.size() - 1) {
                                outputFile << endl << endl;
                            }
                        }
                    }
                }
            }
        }
        counter++;        
    }
    return 0;
}

