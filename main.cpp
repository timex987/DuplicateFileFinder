#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;
using std::filesystem::directory_iterator;



int main(int argc, const char* argv[]) 
{
    stringstream ssTemp;
    ofstream out;
    vector<string> songList, modifiedSongList;
    vector<int> potentialDupes;
    string userDir;

    
    //   Gathering the directory the user wants to check for potential duplicate files
    if (argc == 1)
    {
        cout << "\n\n   Enter in the directory to scan for duplicate files.\n" << endl;
        cout << "   Example: C:\\Users\\Admin\\Desktop\\Folder \n\n\n" << endl;
        cout << "   > ";
        getline(cin, userDir);
        cout << "\n\n" << endl;
    }

    //   Passing in command-line arguments if the user executes the program from the 
    //   command-line interface instead
    else
    {
        userDir = argv[1];
    }


    //   Reading all files in the Music Folder, removing the file path from the resulting
    //   strings, storing them into vectors, and then sorting them
    for (const auto& file : directory_iterator(userDir))
    {
        string temp;

        ssTemp << file.path();

        temp = ssTemp.str();
        
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        size_t foundBKSLSH = temp.find_last_of("\\");
        temp = temp.substr(foundBKSLSH + 1);
        songList.push_back(temp);
        modifiedSongList.push_back(temp);

        ssTemp.clear();
        ssTemp.str("");
    }

    sort(songList.begin(), songList.end());
    sort(modifiedSongList.begin(), modifiedSongList.end());


    //   Removing the file extensions from the file names in the modified vector
    for (int i = 0; i < modifiedSongList.size(); i++)
    {
        size_t foundEXT = modifiedSongList[i].find_last_of(".");
        size_t foundQUOT = modifiedSongList[i].find_last_of("\"");

        if (foundEXT != string::npos)
        {
            modifiedSongList[i].erase(foundEXT);
            songList[i].erase(foundQUOT);
        }
    }

 
    //   Comparing the elements in the modified vector to each other
    //   to determine if there are any potential duplicates, 
    //   and putting the index numbers of potential duplicates into another vector
    for (int i = 0; i < modifiedSongList.size() - 1; i++)
    {
        if (modifiedSongList[i] == modifiedSongList[i + 1])
        {
            potentialDupes.push_back(i);
            potentialDupes.push_back(i + 1);
        }
    }


    //   Removing duplicate index location values from the potentialDupes vector
    for (int i = 0; i < potentialDupes.size() - 1; i++)
    {
        if (potentialDupes[i] == potentialDupes[i + 1])
        {
            potentialDupes[i] = 0;
        }
    }

    sort(potentialDupes.begin(), potentialDupes.end());

    while(true)
    {
        if (potentialDupes[0] == 0)
        {
            potentialDupes.erase(potentialDupes.begin());
        }

        else
        {
            break;
        }
    }

    
    //   Writing the output file and displaying results, if the user started the
    //   program without command-line arguments
    out.open("Results.txt");

    out << "There are " << potentialDupes.size() << " potentially duplicate files!\n\n\n" << endl;
    out << "=====" << endl;

    for (int i = 0; i < potentialDupes.size(); i++)
    {
        out << songList[potentialDupes[i]] << endl;
    }

    out.close();

    if (argc == 1)
    {
        cout << "   There are " << potentialDupes.size() << " potentially duplicate files!\n\n\n" << endl;
        cout << "   Results written to \"Results.txt\".\n\n\n" << endl;
        cout << "   Press Enter to exit." << endl;

        getchar();
    }
}