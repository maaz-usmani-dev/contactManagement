// Contact Management App with CRUD Functionality
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void Add(ofstream &out)
{
    string name, phone, email;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Phone: ";
    getline(cin, phone);
    cout << "Enter Email: ";
    getline(cin, email);

    out << name << "," << phone << "," << email << "\n";
    cout << "Contact added successfully!\n";
}

void Display(ifstream &in)
{
    string line;
    bool found = false;
    while (getline(in, line))
    {
        cout << line << endl;
        found = true;
    }

    if (!found)
    {
        cerr << "No contacts found.\n";
    }
}

void Update(const string &filepath)
{
    string name, line, Data;
    cout << "Enter Name to Update: ";
    cin.ignore();
    getline(cin, name);
    ifstream in(filepath);
    if (!in)
    {
        cerr << "Error in opening file!!\n";
        return;
    }
    bool found = false;
    while (getline(in, line))
    {
        long pos = line.find(",");
        if (pos != string::npos)
        {
            string contact = line.substr(0, pos);
            if (contact == name)
            {
                found = true;
                string name2, phone2, email2;
                cout << "Enter New Name: ";
                getline(cin, name2);
                cout << "Enter New Phone: ";
                getline(cin, phone2);
                cout << "Enter New Email: ";
                getline(cin, email2);

                line = name2 + "," + phone2 + "," + email2;
            }
        }

        Data += line + "\n";
    }

    in.close();

    ofstream out(filepath);
    if (!out)
    {
        cerr << "File cannot be opened!\n";
        return;
    }

    if (found)
    {
        cout << "Contact updated successfully!\n";
    }
    else
    {
        cout << "Contact not found.\n";
    }
    out << Data;
    out.close();
}
void Delete(const string &filepath)
{
    string name, line, Data;
    cout << "Enter Name to Delete: ";
    cin.ignore();
    getline(cin, name);
    ifstream in(filepath);
    if (!in)
    {
        cerr << "Error in opening file!!\n";
        return;
    }
    bool found = false;
    while (getline(in, line))
    {
        long pos = line.find(",");
        if (pos != string::npos)
        {
            string contact = line.substr(0, pos);
            if (contact == name)
            {
                found = true;
                cout << "Deleting Contact: " << contact << endl;
                continue;
            }
        }

        Data += line + "\n";
    }

    in.close();

    ofstream out(filepath);
    if (!out)
    {
        cerr << "File cannot be opened!\n";
        return;
    }

    if (found)
    {
        cout << "Contact deleted successfully!\n";
    }
    else
    {
        cout << "Contact not found.\n";
    }
    out << Data;
    out.close();
}

int main()
{
    char choice;
    const string filepath = "./Contacts.csv";
    while (true)
    {
        cout << "\n-------------Contact Management app----------------\n";
        cout << "\n1. Add New Contact          \n"
             << "2. Display Contacts         \n"
             << "3. Update Existing Contact  \n"
             << "4. Delete Contact           \n"
             << "5. Exit                     \n";
        cout << "Enter choice: ";
        cin >> choice;

        ifstream in;
        ofstream out;

        switch (choice)
        {
        case '1':
            out.open(filepath, ios::app);
            if (!out)
            {
                cerr << "File cannot be opened!\n";
                return 1;
            }
            Add(out);
            out.close();
            break;
        case '2':
            in.open(filepath);
            if (!in)
            {
                cerr << "File not found!\n";
                return 1;
            }
            Display(in);
            in.close();
            break;
        case '3':
            Update(filepath);
            break;
        case '4':
            Delete(filepath);
            break;
        case '5':
            cout << "Program Exited Successfully...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
