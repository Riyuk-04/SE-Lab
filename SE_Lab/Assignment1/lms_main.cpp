//***********************************Seg Fault in Heretics.txt in chapters and in Moby Dick in paragraphs**********************************
#include <bits/stdc++.h> 
#include <dirent.h>
#include <sys/types.h>
#include <cctype>
#include <iostream>
#include <cstring> 

using namespace std;

class books{
public:
   string filename;
   string author;
   string title;
   string release_date;
   string language;
   string type;
   string path;

   void print_obj(){
      cout<<"File name:"<<this->filename<<endl;
      cout<<"Title:"<<this->title<<endl;
      cout<<"Author:"<<this->author<<endl;
      //cout<<"Release Date:"<<this->release_date<<endl;
      cout<<"Language:"<<this->language<<endl;
      cout<<"Type:"<<this->type<<endl;
   }

   void print_obj_fta(){
      cout<<"File name: "<<this->filename<<endl;
      cout<<"Title: "<<this->title<<endl;
      cout<<"Author: "<<this->author<<endl<<endl;
   }

   void print_obj_ta(){
      cout<<"Title: "<<this->title<<endl;
      cout<<"Author: "<<this->author<<endl<<endl;
   }
};

class novel: public books{
public:
   int top_k = 5;
   novel(books book){
      path = book.path;
      title = book.title;
      author = book.author;
   }

   void diplay_nth_para(int n){
      int check = 0;
      string line;
      fstream file;
      file.open(this->path, ios::in);
      while(getline(file, line)){
         if(line.length()==1) check++;
         if(check == n)
            puts(line.c_str());
         if(check > n) break;
      }
      file.close();
      return;
   }

   //TODO: Segfault in mobi dick  ???????????????????????????????????????????????????????????????????????????????
   void display_topk_par(){
      string word;
      cout<<"Enter the word:";
      cin>>word;
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      cout<<"Enter the value of k:";
      cin>>this->top_k;

      int word_count = 0;
      std::vector<int> count_per_para;
      string line;
      ifstream file;
      file.open(this->path, ios::in);
      while(getline(file, line)){
         if(line.length()==1){
            count_per_para.push_back(word_count);
            word_count = 0;
         }
         else{
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            stringstream ss(line);
            while(ss>>line)
               if(line==word || line == (word + ".") || line == (word + ",") || line == (word + ";") || line == (word + "?"))
                  word_count++;
         }
      }
      file.close();

      cout<<"Top "<<this->top_k<<" paragraphs are: "<<endl;
      for (int i = 0; i < this->top_k; ++i){
         cout<<"****************************************"<<endl;
         int x = (max_element(count_per_para.begin(), count_per_para.end()) - count_per_para.begin());
         if(count_per_para[x] != 0)   {cout<<"Count : "<<count_per_para[x]<<endl;   diplay_nth_para(x);}
         else  {cout<<"No more paragraphs with the word "<<word<<endl; break;}
         count_per_para[x] = -1;
      }
   }

   void display_topk_chapter(){
      string word;
      cout<<"Enter the word:";
      cin>>word;
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      cout<<"Enter the value of k:";
      cin>>this->top_k;

      int flag = 0;
      int word_count = 0;
      std::vector<int> count_per_chapter;
      string line;
      ifstream file;
      file.open(this->path, ios::in);
      while(file>>line){
         if(line == "CHAPTER"){
            if(flag == 1)  count_per_chapter.push_back(word_count);
            word_count = 0;
            flag = 1;
         }

         transform(line.begin(), line.end(), line.begin(), ::tolower);
         if(line == word || line == (word + ".") || line == (word + ",") || line == (word + ";") || line == (word + "?"))  word_count++;
      }
      file.close();

      cout<<"Top "<<this->top_k<<" chapters are: "<<endl;
      for (int i = 0; i < this->top_k; ++i){
         cout<<"****************************************"<<endl;
         int x = (max_element(count_per_chapter.begin(), count_per_chapter.end()) - count_per_chapter.begin());
         if(count_per_chapter[x] != 0)   cout<<"CHAPTER : "<<x+1<<"          count : "<<count_per_chapter[x]<<endl;
         else  {cout<<"No more chapters with the word "<<word<<endl; break;}
         count_per_chapter[x] = -1;
      }
   }

};

class play: public books{
public:
   play(books book){
      path = book.path;
      title = book.title;
      author = book.author;
   }

   void display_scene_char(string char_name){
      set<string> scene_chars;
      set<string> all_chars;
      string word;
      int scene_index = 0;
      int flag = 0;
      int index = 1;
      string line;
      ifstream file;
      file.open(this->path, ios::in);
      while(getline(file, line)){
         
         if(line.find(".") != std::string::npos && flag == 1){
            size_t pos = strchr(line.c_str(),'.') - line.c_str();
            line = line.substr(0, pos);
            stringstream ss(line);
            ss>>word;
            if (std::all_of(line.begin(), line.end(), [](char c){if(c == 32)return 1; return std::isupper(c); }) && word!="SCENE" && word!="ACT" && line.length() > 2)
               scene_chars.insert(line);
         }

         if(line.find("SCENE") != std::string::npos){
            flag = 1;
            if(scene_chars.count(char_name)){
               for(auto it = scene_chars.begin(); it != scene_chars.end(); it++)
                  all_chars.insert(*it);
            }
            scene_chars.clear();
         }
      }
      if(scene_chars.count(char_name)){
         for(auto it = scene_chars.begin(); it != scene_chars.end(); it++)
            all_chars.insert(*it);
      }
      file.close();

      cout<<"All characters in any scene with: "<<char_name<<endl;
      for(auto it = all_chars.begin(); it != all_chars.end(); it++)
        std::cout<<index++<<":"<<*it<< endl;
   }

   void display_characters(){
      set<string> all_chars;
      string line;
      string word;

      ifstream file;
      file.open(this->path, ios::in);
      while(getline(file, line)){

         if(line.find(".") != std::string::npos){
            size_t pos = strchr(line.c_str(),'.') - line.c_str();
            line = line.substr(0, pos);
            stringstream ss(line);
            ss>>word;
            if (std::all_of(line.begin(), line.end(), [](char c){if(c == 32)return 1; return std::isupper(c); }) && word!="SCENE" && word!="ACT" && line.length() > 2)
               all_chars.insert(line);
         }
      }
      file.close();
      
      int index = 1;
      cout<<"All Characters:"<<endl;
      for(auto it = all_chars.begin(); it != all_chars.end(); it++)
        cout<<index++<<":"<<*it<< endl;
      cout<<"Please enter the id of a character:"<<endl;

      while(1){
         cin>>index;
         if(index <= 0 || index > all_chars.size())
            cout<<"Enter a valid id!!!";
         else break;
      }
      auto it = all_chars.begin();
      for (int i = 1; i < index; ++i)  it++;
      string char_name = *it;
      display_scene_char(char_name);
   }
};

void partial_parse(vector<books>& books_vec, vector<string> index_types, vector<string> index_titles, string dir_path){
   
   fstream file;
   for (int i = 0; i < index_titles.size(); ++i){
      string word;
      string line;
      books this_book;
      this_book.type = index_types[i];
      this_book.filename = index_titles[i];
      this_book.path = dir_path + "/" + index_titles[i];
      file.open(dir_path + "/" + index_titles[i], ios::in);
      while(word != "***"){
         file>>word;
         if(word == "Title:"){
            getline(file, line);
            line.erase(0,1);
            this_book.title = line;
         }
         if(word == "Author:"){
            getline(file, line);
            line.erase(0,1);
            this_book.author = line;
         }
         if(word == "Language:"){
            getline(file, line);
            line.erase(0,1);
            this_book.language = line;
         }
      }
      books_vec.push_back(this_book);
      file.close();
   }
}

void check_index(vector<string>& books_name, vector<string>& index_titles_new, vector<string>& index_types_new){

   //Reading index.txt
   vector<string> index_titles_old;
   vector<string> index_types_old;
   string word;
   fstream index;
   index.open("index.txt", ios::in);
   while(index>>word){
      index_titles_old.push_back(word);
      index>>word;
      index_types_old.push_back(word); 
   }
   index.close();

   //Checking and adding/deleting books
   string type;
   index.open("index.txt", ios::out);
   for (int i = 0; i < books_name.size(); ++i){

      auto it = std::find (index_titles_old.begin(), index_titles_old.end(), books_name[i]);
      if (it == index_titles_old.end()){
         cout<<"Found new book by the name of "<<books_name[i].substr(0,books_name[i].length()-4)<<endl;
         cout<<"Enter the type of "<<books_name[i].substr(0,books_name[i].length()-4)<<": ";
         cin>>type;
      }
      else
         type = index_types_old[it - index_titles_old.begin()];

      index<<books_name[i]<<" "<<type<<endl;
      index_titles_new.push_back(books_name[i]);
      index_types_new.push_back(type);
   }
   index.close();
}

void diplay_book(books book){

   char yn = 'y';
   string line;
   fstream file_book;
   file_book.open(book.path, ios::in);
   while(tolower(yn) == 'y'){
      for (int i = 0; i < 100; ++i){
         getline(file_book, line);
         cout<<line<<endl;
      }
      cout<<endl<<"Do you wish to see more [y/n]:";
      cin>>yn;
   }
}

void search_book(vector<books>& books_vec){
   int input;
   string text;
   string temp;
   cout<<"Search using:"<<endl<<"1-> Title"<<endl<<"2-> Author"<<endl;
   cin>>input;
   int count = 1;

   vector<books> searched_books;
   if(input == 1){
      cout<<"Enter Title:";
      cin.ignore();
      getline(cin, text);
      transform(text.begin(), text.end(), text.begin(), ::tolower);
      for (int i = 0; i < books_vec.size(); ++i){
         temp = books_vec[i].title;
         transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
         if(temp.find(text) != std::string::npos){
            cout<<endl<<"Book id:"<<count++<<endl;
            books_vec[i].print_obj();
            cout<<endl;
            searched_books.push_back(books_vec[i]);
         }
      }
   }
   else if(input == 2){
      cout<<"Enter Author:";
      cin.ignore();
      getline(cin, text);
      transform(text.begin(), text.end(), text.begin(), ::tolower);
      //cout<<endl<<"Seaching for **"<<text<<"** in author"<<endl;
      for (int i = 0; i < books_vec.size(); ++i){
         temp = books_vec[i].author;
         transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
         if(temp.find(text) != std::string::npos){
            cout<<"Book id:"<<count++<<endl;
            books_vec[i].print_obj();
            cout<<endl;cout<<endl;
            searched_books.push_back(books_vec[i]);
         }
      }
   }
   else{
      cout<<"Select a valid input!!!"<<endl;
      cin.clear();
      return;
   }

   char yn = 'n';
   int index;
   if(searched_books.size() == 0)
      cout<<"No search found"<<endl;
   if(searched_books.size() == 1){
      cout<<"Do you want to see the book[y/n]:";
      cin>>yn;
      if(tolower(yn) == 'y')
         diplay_book(searched_books[0]);
   }
   if(searched_books.size() > 1){
      while(1){   
         cout<<"Enter the book's id to be displayed(0 if not to display):";
         cin>>index;
         if(index >= 1 && index <= searched_books.size()){
            diplay_book(searched_books[index-1]);
            break;
         }
         else if(index == 0)
            return;
         else
            cout<<"Please enter a valid index"<<endl;
      }
   }
}

void search_word(vector<books>& books_vec){
   std::vector<novel> all_novels;
   for (int i = 0; i < books_vec.size(); ++i){
      if(books_vec[i].type == "novel"){
         novel temp = novel(books_vec[i]);
         all_novels.push_back(temp);
      }
   }

   int id;
   int flag;
   cout<<"All listed novels are: "<<endl;
   for (int i = 0; i < all_novels.size(); ++i){
      cout<<"Novel id: "<<i+1<<endl;
      all_novels[i].print_obj_ta();
   }
   while(1){
      cout<<"Please select a novel id: ";
      cin>>id;
      if(id <=0 || id > all_novels.size())
         cout<<"Invalid id!!!";
      else  break;
   }
   while(1){
      cout<<"Display paragraphs-> 1"<<endl<<"Display chapters-> 2"<<endl;
      cin>>flag;
      if(flag !=1 && flag!=2)
         cout<<"Invalid input!!!"<<endl;
      else
         break;
   }
   if(flag == 1)
      all_novels[id-1].display_topk_par();
   if(flag == 2)
      all_novels[id-1].display_topk_chapter();
}

void search_character(vector<books>& books_vec){
   std::vector<play> all_plays;
   for (int i = 0; i < books_vec.size(); ++i){
      if(books_vec[i].type == "play"){
         novel temp = play(books_vec[i]);
         all_plays.push_back(temp);
      }
   }

   int id;
   cout<<"All listed plays are: "<<endl;
   for (int i = 0; i < all_plays.size(); ++i){
      cout<<"Play id: "<<i+1<<endl;
      all_plays[i].print_obj_ta();
   }
   while(1){
      cout<<"Please select a play id: ";
      cin>>id;
      if(id <=0 || id > all_plays.size())
         cout<<"Invalid id!!!";
      else  break;
   }
   all_plays[id-1].display_characters();
}

std::vector<string> list_dir(const char *path) {
   struct dirent *entry;
   DIR *dir = opendir(path);
   vector<string> v;

   if (dir == NULL) {
      return v;
   }
   while ((entry = readdir(dir)) != NULL){
      if( strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
         v.push_back(entry->d_name);
   }
   closedir(dir);
   return v;
}

void print_menu(){
   cout<<"****************************************************************************"<<endl;
   cout<<"0-> Print menu"<<endl;
   cout<<"1-> List all books"<<endl;
   cout<<"2-> Search and display a book by its title or author name"<<endl;
   cout<<"3-> Search for a word in a novel"<<endl;
   cout<<"4-> Search for a characters in a play"<<endl;
}

int main(int argc, char const *argv[])
{
   //Creating a vector books_name that stores file names of all files in directory
   string dir_path = argv[2];
   std::vector<string> books_name;
   books_name = list_dir(argv[2]);

   //Declaring variables and vectors
   std::vector<string> index_titles;
   std::vector<string> index_types;
   std::vector<books> books_vec;
   int input = 0;
   int index_input = 0;

   //Updating index.txt with insertions and deletions
   check_index(books_name, index_titles, index_types);

   partial_parse(books_vec, index_types, index_titles, dir_path);

   while(1){
      switch (input) 
      { 
         case 0: 
            print_menu(); 
            break;
         case 1:
            for (int i = 0; i < books_vec.size(); ++i){
               cout<<"Book id :"<<i+1<<endl;
               books_vec[i].print_obj_fta();
            }
            cout<<"Enter the book's id to be displayed(0 if not to display):";
            cin>>index_input;
            if(index_input > books_vec.size())
               cout<<"Invalid id"<<endl;
            else if(index_input != 0)
               diplay_book(books_vec[index_input-1]);
            break;
         case 2:
            search_book(books_vec);
            break;
         case 3:
            search_word(books_vec);
            break;
         case 4:
            search_character(books_vec);
            break;
         default:
            cout<<"Choose a valid input"<<endl;  
      }
      cout<<"****************************************************************************"<<endl;
      cout<<"Please enter an input(0 to print menu): ";
      cin>>input;
   }

   return 0;
}