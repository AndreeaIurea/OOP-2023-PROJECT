#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <typeinfo>



class Step //clasa pt un pas
{
public:
    virtual void execute() = 0; //executarea unui pas
    virtual void DisplayStepInfo() const = 0; //afisarea detaliilor specifice fiecarui pas
    virtual std::string GetStepName() const = 0; //returneaza numele unui pas
    virtual void DetailsToFile(std::ofstream& file) const = 0; //la fiecare pas, scrie detaliile in fisier
    virtual ~Step() = default;
    virtual std::string GetStepType() const = 0;

};

class TITLEstep: public Step //clasa pt pasul TITLE
{
private:
    std::string title;
    std::string subtitle;

public:
    TITLEstep(const std::string &t, const std::string &st)
    {
        title = t;
        subtitle = st;
    }

    void execute() override
    {}

    void DisplayStepInfo() const override
    {
        std::cout << "TITLE Step: " << "\n";
        std::cout << "Title: " << title << "\n";
        std::cout << "Subtitle: " << subtitle << "\n";
    }

    virtual std::string GetStepType() const override
    {

    }

    std::string GetStepName() const override
    {
        return "TITLE";
    }

    void DetailsToFile(std::ofstream &file) const override
    {
        file << "TITLE Step: " << "\n";
        file << "Title: " << title << "\n";
        file << "Subtitle: " << subtitle << "\n";
    }
};



class TEXTstep: public Step //clasa pt pasul TEXT
{
private:
    std::string title;
    std::string copy;

public:
    TEXTstep(const std::string& t, const std::string& c)
    {
        title = t;
        copy = c;
    }

    void execute() override
    {
    }

    virtual std::string GetStepType() const override
    {

    }

    std::string GetStepName() const override
    {
        return "TEXT";
    }


    void DisplayStepInfo() const override
    {
        std::cout << "TEXT Step: " << "\n";
        std::cout << "Title: " << title <<"\n";
        std::cout << "Copy: "<< copy << "\n";

    }

    void DetailsToFile(std::ofstream& file) const override
    {
        file << "TEXT Step: " << "\n";
        file << "Title: " << title << "\n";
        file << "Copy: " << copy << "\n";
    }

};




class TEXTINPUTstep: public Step //clasa pt pasul TEXT INPUT
{
private:
    std::string description;
    std::string textinput;

public:

    void AddDescription(const std::string& d)
    {
        description = d;
    }

    void AddTextInput(const std::string& ti)
    {
        textinput = ti;
    }

    virtual std::string GetStepType() const override
    {

    }

    std::string GetTextInput() const
    {
        return textinput;
    }

    std::string GetDescription() const
    {
        return description;
    }

    void execute() override
    {
    }

    std::string GetStepName() const override
    {
        return "TEXT INPUT";
    }


    void DisplayStepInfo() const override
    {
        std::cout << "TEXT INPUT Step: " << "\n";
        std::cout << "Description: " << description <<"\n";
        std::cout << "Text Input: "<< textinput << "\n";

    }

    void DetailsToFile(std::ofstream& file) const override
    {
        file << "TEXT INPUT Step: " << "\n";
        file << "Description: " << description <<"\n";
        file << "Text Input: "<< textinput << "\n";
    }
};





class NUMBERINPUTstep : public Step
{
private:
    std::string description;
    float numberinput;

public:
    void AddDescription(const std::string &d)
    {
        description = d;
    }

    void AddNumberInput(float nr)
    {
        numberinput = nr;
    }
    virtual std::string GetStepType() const override
    {

    }

    float GetNumberInput() const
    {
        return numberinput;
    }

    std::string GetDescription() const
    {
        return description;
    }

    void execute() override
    {
    }

    std::string GetStepName() const override
    {
        return "NUMBER INPUT";
    }

    float getValue() const
    {
        return numberinput;
    }

    void DisplayStepInfo() const override
    {
        std::cout << "NUMBER INPUT Step: " << "\n";
        std::cout << "Description: " << description << "\n";
        std::cout << "Number Input: " << GetNumberInput() << "\n";
    }

    void DetailsToFile(std::ofstream &file) const override
    {
        file << "NUMBER INPUT Step: " << "\n";
        file << "Description: " << description << "\n";
        file << "Number Input: " << numberinput << "\n";
    }
};

template <typename T>
class CALCULUSstep : public Step
{
private:
    int steps;
    std::string operation;
    T result; // Rezultatul operației


public:
    CALCULUSstep(int s, const std::string &o) : steps(s), operation(o), result(0) {}



    void execute() override
    {

    }


    T Calcul(T n1, T n2)
    {
        if (!(n1!=0 && n2!=0))
        {
            std::cout << "Trebuie sa adaugati cel putin doi pasi NUMBER INPUT pentru a realiza operații CALCULUS.\n";
            return 0;
        }


        if (operation == "+")
        {
            result = n1 + n2;
        }
        else if (operation == "-")
        {
            result = n1 - n2;
        }
        else if (operation == "*")
        {
            result = n1 * n2;
        }
        else if (operation == "/")
        {
            if (n2 != 0)
                result = n1 / n2;
            else
                std::cout << "Nu se poate împărți la zero." << std::endl;
        }
        else if (operation == "min")
        {
            result = std::min(n1, n2);
        }
        else if (operation == "max")
        {
            result = std::max(n1, n2);
        }
        else
        {
            std::cout << "Operație necunoscută." << std::endl;
            return 0;
        }
        return result;

    }

    T GetResult()
    {
        return result;
    }


    std::string GetStepType() const override
    {
        return "CALCULUS<" + std::string(typeid(T).name()) + ">";

    }



    std::string GetStepName() const override
    {
        return "CALCULUS";
    }

    void DisplayStepInfo() const override
    {
        std::cout << "CALCULUS Step: " << "\n";
        std::cout << "Steps: " << steps << "\n";
        std::cout << "Operation: " << operation << "\n";
        std::cout << "Result: " << result << "\n";



        std::cout << "\n";
    }

    void DetailsToFile(std::ofstream &file) const override
    {
        file << "CALCULUS Step: " << "\n";
        file << "Steps: " << steps << "\n";
        file << "Operation: " << operation << "\n";
        file << "Result: " << result << "\n";
    }
};





class TEXTFILEINPUTstep: public Step //clasa pt TEXT FILE INPUT step
{
private:
    std::string description, file_name;



public:

    void AddDescription(const std::string& d)
    {
        description = d;
    }

    void AddFileName(const std::string& fn)
    {
        file_name = fn;
    }
    virtual std::string GetStepType() const override
    {

    }

    std::string GetFileName() const
    {
        return file_name;
    }

    std::string GetDescription() const
    {
        return description;
    }

    void execute() override
    {

    }

    std::string GetStepName() const override
    {
        return "TEXT FILE INPUT";
    }

    void DisplayStepInfo() const override
    {
        std::cout << "TEXT FILE INPUT:\n" << "Description: " << description <<"\nFile name: "<<file_name<<"\n";
    }

    void DetailsToFile(std::ofstream& file) const override
    {
        file << "TEXT FILE INPUT:\n";
        file << "Description: " << description << "\n";
        file << "File name: " << file_name << "\n";
    }

    void writeParametersToFile() const
    {
        std::ofstream paramsFile(file_name + ".txt");
        if (paramsFile.is_open())
        {
            paramsFile << "Descriere: " << description <<std::endl;
            paramsFile << "Nume fisier: " << file_name <<std::endl;
            paramsFile.close();
            std::cout << "Parametrii pasului TEXT FILE input au fost scrisi in fisierul " << file_name << ".txt" <<std::endl;
        }
        else
        {
            std::cout << "Nu s-a putut crea fisierul pentru parametrii pasului TEXT FILE input." <<std::endl;
        }
    }
};




class CSVFILEINPUTstep: public Step //clasa pt pasul CSV FILE INPUT
{
private:
    std::string description, file_name;

public:
    void AddDescription(const std::string& d)
    {
        description = d;
    }
    virtual std::string GetStepType() const override
    {

    }

    void AddFileName(const std::string& fn)
    {
        file_name = fn;
    }

    std::string GetFileName() const
    {
        return file_name;
    }

    std::string GetDescription() const
    {
        return description;
    }

    void execute() override
    {

    }

    void writeParametersToFile() const
    {
        std::ofstream paramsFile(file_name + ".csv");
        if (paramsFile.is_open())
        {
            paramsFile << "Descriere: " << description << std::endl;
            paramsFile << "Nume fisier: " << file_name << std::endl;
            paramsFile.close();
            std::cout << "Parametrii pasului CSV FILE input au fost scrisi in fisierul " << file_name << ".csv" << std::endl;
        }
        else
        {
            std::cout << "Nu s-a putut crea fisierul pentru parametrii pasului CSV FILE input." << std::endl;
        }
    }

    std::string GetStepName() const override
    {
        return "CSV FILE INPUT";
    }

    void DisplayStepInfo() const override
    {
        std::cout << "CSV FILE INPUT:\n" << "Description: " << description <<"\nFile name: "<<file_name<<"\n";
    }

    void DetailsToFile(std::ofstream& file) const override
    {
        file << "CSV FILE INPUT:\n";
        file << "Description: " << description << "\n";
        file << "File name: " << file_name << "\n";
    }
};


class DISPLAYstep: public Step //clasa pt pasul DISPLAY
{
private:
    int step;
    std::string displayFileType;

public:
    DISPLAYstep(int s,const std::string& type)
    {
        step = s;
        displayFileType = type;
    }

    void DisplayStepInfo() const override
    {
        std::cout << "DISPLAY STEPS: \n";
        std::cout << "Step: " << step << "\n";
    }

    virtual std::string GetStepType() const override
    {

    }

    void execute() override
    {

    }

    std::string GetStepName() const override
    {
        return "DISPLAY";
    }

    void DetailsToFile(std::ofstream& file) const override
    {
        file << "DISPLAY STEPS: \n";
        file << "Step: " << step << "\n";
    }

    void displayFileContent() const //Afisam continutul fisierului asociat pasului TEXTFILEINPUTtep sau CSVFILEINPUTStep
    {
        std::string fileExtension = (displayFileType == "txt") ? "_params.txt" : "_params.csv";
        std::string fileName = (displayFileType == "txt") ? "nume_fisier_text" : "nume_fisier_csv";

        std::ifstream fileToDisplay(fileName + fileExtension);
        if (fileToDisplay.is_open())
        {
            std::string line;
            while (getline(fileToDisplay, line))
            {
                std::cout << line << "\n";
            }
            fileToDisplay.close();
        }
        else
        {
            std::cout << "Nu s-a putut citi fisierul asociat pasului TextFileInputStep sau CSVFileInputStep.\n";
        }
    }

};



class  OUTPUTstep: public Step //clasa pt pasul OUTPUT
{
private:
    int step;
    std::string file_name, title, description;
    std::vector<std::string> information; //informatii de la pasii anteriori

public:
    OUTPUTstep(int s, const std::string& fn, const std::string& t, const std::string& d)
    {
        step = s;
        file_name =  fn;
        title = t;
        description = d;
    }

    virtual std::string GetStepType() const override
    {

    }

    void execute() override
    {

    }

    std::string GetStepName() const override
    {
        return "OUTPUT";
    }

    void DisplayStepInfo() const override
    {
        std::cout << "OUTPUT STEP:\n";
        std::cout << "Step: " << step <<std::endl;
        std::cout << "File name: " << file_name <<std::endl;
        std::cout << "Title: "<< title <<std::endl;
        std::cout << "Description: " << description <<std::endl;
    }

    void DetailsToFile(std::ofstream& file) const override
    {
        file << "OUTPUT STEP:\n" <<std::endl;
        file << "Step: " << step <<std::endl;
        file << "File Name: " << file_name <<std::endl;
        file << "Title: " << title <<std::endl;
        file << "Description: " << description <<std::endl;
    }

};


//clasa pt pasul END
class ENDstep: public Step
{

    std::string GetStepName() const override
    {
        return "END";
    }

    void DisplayStepInfo() const override
    {
        std::cout << "Sfarsitul flow-ului" <<std::endl;
    }

    virtual std::string GetStepType() const override
    {

    }

    void writeDetailsToFile(std::ofstream &file) const
    {
        file << "Sfarsitul flow-ului" <<std::endl;
    }
};



class Flow //clasa pentru tot ce tine de un flow
{
private:
    static const int maxSteps = 50; //presupunem ca un flow este format din maxim 50 de pasi
    Step* steps[maxSteps];
    int current_step;
    std::string flowName;

    //Variabila pentru a contoriza cate ori a fost inceput flow-ul
    int startedCount;

    //Variabila pentru a contoriza câte ori a fost completat cu sau fără erori
    int completedCount;

    //Un dictionar (unordered_map) pentru a tine evidenta cat de des a fost sarit fiecare ecran
    std::unordered_map<std::string, int> skippedScreens;

    // Un dictionar (unordered_map) pentru a tine evidenta cat de des a fost afisat un ecran de eroare pentru fiecare pas
    std::unordered_map<std::string, int> errorScreens;

    // Variabila pentru a contoriza numarul total de erori in toate flow-urile completate
    int totalErrors;





public:
    Flow()
    {
        current_step = 0;
    }

    template <typename T>
    CALCULUSstep<T>* CastToCALCULUSstep(Step* step)
    {
        return dynamic_cast<CALCULUSstep<T>*>(step);
    }

    void SetFlowName(const std::string& name) // Adăugați o metodă pentru a seta numele flow-ului
    {
        flowName = name;
    }

    std::string GetFlowName() const // Adăugați o metodă pentru a obține numele flow-ului
    {
        return flowName;
    }

    void AddStep(Step* step) //adaugare pas la un proces
    {
        if(current_step < maxSteps )
            steps[current_step++] = step;
        else
        {
            std::cout << "S-a atins nr. maxim de pasi. \n";
            delete step;
        }
    }

    //Metoda pentru a incepe un flow si a incrementa contorul de începuturi
    void StartFlow()
    {
        startedCount++;

    }

    //Metoda pentru a finaliza un flow si a marca daca a avut erori sau nu
    void CompleteFlow(bool hasErrors)
    {
        completedCount++;

        //Daca flow-ul a avut erori, incrementam contorul total de erori
        if (hasErrors)
            totalErrors++;



    }

    //Metoda pentru a inregistra ca un ecran a fost sarit
    void ScreenSkipped(const std::string& screenName)
    {
        skippedScreens[screenName]++;
    }

    //Metoda pentru a inregistra ca un ecran de eroare a fost afisat
    void ErrorScreenDisplayed(const std::string& screenName)
    {
        errorScreens[screenName]++;
    }


    //Metoda pentru a obtine numarul de inceputuri de flow
    int GetStartedCount() const
    {
        return startedCount;
    }

    int GetTotalErrors() const
    {
        return totalErrors;
    }

    //Metoda pentru a obtine numarul de flow-uri completate
    int GetCompletedCount() const
    {
        return completedCount;
    }

    // Metoda pentru a obtine numarul de ori cand un anumit ecran a fost sarit
    int GetSkippedScreenCount(const std::string& screenName) const
    {
        auto it = skippedScreens.find(screenName);
        return (it != skippedScreens.end()) ? it->second : 0;
    }

    // Metoda pentru a obtine numarul de ori cand un ecran de eroare a fost afisat pentru un anumit pas
    int GetErrorScreenCount(const std::string& screenName) const
    {
        auto it = errorScreens.find(screenName);
        return (it != errorScreens.end()) ? it->second : 0;
    }

    // Metoda pentru a obtine media numarului de erori per flow completat
    double GetAverageErrorsPerFlow() const
    {
        // Verificam daca au fost completate flow-uri pentru a evita impartirea la zero

        return (completedCount > 0) ? static_cast<double>(totalErrors) / completedCount : 0.0;
    }


    const std::unordered_map<std::string, int>& GetErrorScreens() const
    {
        return errorScreens;
    }




    void DisplayFlowInfo() const //afiseaza informatii despre pasii dintr un flow
    {
        int i;
        if(current_step > 0)
        {
            for(i=0; i<current_step; i++)
                steps[i]->DisplayStepInfo();
            std::cout<<"\n";
        }
        else
            std::cout << "Nu exista pasi in acest flow.\n";


    }

    void ExecuteFlow() //executa toti pasii din flow, asigurandu-se ca fluxul este liniar
    {
        for(int i=0; i<current_step; i++)
            steps[i]->execute();
    }

    void WriteToFile(std::ofstream& file)  //scrie detaliile fiecarui pas intr un fisier
    {
        if(file.is_open())
        {
            for(int i=0; i<current_step; i++)
                steps[i]->DetailsToFile(file);
            file<<std::endl;
            file.close();
        }
        else
            std::cout << "Fisierul nu s-a putut deschide.\n";
    }


    int GetStepsNumber() const //returneaza nr de pasi din flow
    {
        return current_step;
    }

    Step *GetStep(int s) const //returneaza un anumit pas din flow
    {
        if (s>= 0 && s < current_step)
        {
            return steps[s];
        }
        return nullptr;
    }

    const std::unordered_map<std::string, int>& GetSkippedScreens() const
    {
        return skippedScreens;
    }


    void skipStep(Step* StepToSkip) //elimina un pas din flow
    {
        //cauta pasul in flow si il elimina
        for(int i=0; i<current_step; ++i)
        {
            if (steps[i]==StepToSkip)
            {
                delete steps[i];
                for(int j = i; j<current_step - 1; ++j)

                    steps[j] = steps[j + 1];

                --current_step;
                break;
            }
        }
    }




};

//Funcție pentru a obtine timestamp-ul curent ca sir de caractere
std::string GetCurrentTimestamp()
{
    auto acum = std::chrono::system_clock::now();
    std::time_t timpCurent = std::chrono::system_clock::to_time_t(acum);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timpCurent), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}


void CreateNewFlow(Flow& flow) //functie pt crearea "scheletului" unui flow
//acelasi tip de pas poate fi adaugat de mai multe ori
{
    char choice;
    std::string flowName;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignora newline-ul rămas în buffer
    std::cout << "Introduceti denumirea pentru noul flow: ";
    std::getline(std::cin, flowName);

    flow.SetFlowName(flowName);

    // Obține timestamp-ul curent
    std::string timestamp = GetCurrentTimestamp();


    do
    {
        std::cout << "Alegeti o optiune pentru noul flow:\n";
        std::cout << "1. Adauga pas TITLE\n";
        std::cout << "2. Adauga pas TEXT\n";
        std::cout << "3. Adauga pas TEXT INPUT\n";
        std::cout << "4. Adauga pas NUMBER INPUT\n";
        std::cout << "5. Adauga pas CALCULUS\n";
        std::cout << "6. Adauga pas DISPLAY\n";
        std::cout << "7. Adauga pas TEXT FILE INPUT\n";
        std::cout << "8. Adauga pas CSV FILE INPUT\n";
        std::cout << "9. Adauga pas OUTPUT\n";
        std::cout << "0. Iesire\n";

        std::cin >> choice;

        switch (choice)
        {
        case '1':
        {
            //Adaugare pas TITLE
            std::string title, subtitle;
            std::cout << "Introduceti titlul: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            if (title.empty())
            {
                std::cout << "Atentie! Titlul nu poate fi gol. Incercati din nou.\n";
                std::cout << "Doriti sa reincercati pasul TITLE? (y/n): ";
                char retryChoice;
                std::cin >> retryChoice;
                if (retryChoice == 'y' || retryChoice == 'Y')
                {
                    continue;  // Reincercam pasul TITLE
                }
                else
                {
                    // Daca utilizatorul nu vrea sa reincerce, iesim din bucla
                    break;
                }
            }
            std::cout << "Introduceti subtitlul: ";
            std::getline(std::cin, subtitle);
            if (subtitle.empty())
            {
                std::cout << "Atentie! Subtitlul nu poate fi gol. Incercati din nou.\n";
                std::cout << "Doriti sa reincercati pasul TITLE? (y/n): ";
                char retryChoice;
                std::cin >> retryChoice;
                if (retryChoice == 'y' || retryChoice == 'Y')
                {
                    continue;  // Reincercam pasul TITLE
                }
                else
                {
                    // Daca utilizatorul nu vrea sa reincerce, iesim din bucla
                    break;
                }
            }
            flow.AddStep(new TITLEstep(title, subtitle));

            break;
        }
        case '2':
        {
            //Adaugare pas TEXT
            std::string title, copy;
            std::cout << "Introduceti titlul: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            if (title.empty())
            {
                std::cout << "Atentie! Titlul nu poate fi gol. Incercati din nou.\n";
                std::cout << "Doriti sa reincercati pasul TEXT? (y/n): ";
                char retryChoice;
                std::cin >> retryChoice;
                if (retryChoice == 'y' || retryChoice == 'Y')
                {
                    continue;  // Reincercam pasul TITLE
                }
                else
                {
                    // Daca utilizatorul nu vrea sa reîncerce, iesim din bucla
                    break;
                }
            }
            std::cout << "Introduceti textul: ";
            std::getline(std::cin, copy);
            if (copy.empty())
            {
                std::cout << "Atentie! Copia nu poate fi goala. Incercati din nou.\n";
                std::cout << "Doriti sa reincercati pasul TEXT? (y/n): ";
                char retryChoice;
                std::cin >> retryChoice;
                if (retryChoice == 'y' || retryChoice == 'Y')
                {
                    continue;  // Reincercam pasul TITLE
                }
                else
                {
                    // Daca utilizatorul nu vrea sa reîncerce, iesim din bucla
                    break;
                }
            }
            flow.AddStep(new TEXTstep(title, copy));

            break;
        }
        case '3':
        {
            // Adăugare pas TEXT INPUT
            std::string description;
            std::cout << "Introduceti descrierea: ";
            std::cin.ignore();
            std::getline(std::cin, description);
            if (description.empty())
            {
                std::cout << "Atentie! Descrierea nu poate fi goala. Incercati din nou.\n";
                std::cout << "Doriti sa reincercati pasul TEXTINPUT? (y/n): ";
                char retryChoice;
                std::cin >> retryChoice;
                if (retryChoice == 'y' || retryChoice == 'Y')
                {
                    continue;  // Reincercam pasul TITLE
                }
                else
                {
                    // Daca utilizatorul nu vrea sa reîncerce, iesim din bucla
                    break;
                }
            }

            // Creare și adăugare pas TEXTINPUTstep în flow
            TEXTINPUTstep* textInputStep = new TEXTINPUTstep();
            textInputStep->AddDescription(description);
            flow.AddStep(textInputStep);
            break;
        }

        case '4':
        {
            //Adaugare pas NUMBER INPUT
            std::string description;
            std::cout << "Introduceti descrierea: ";
            std::cin.ignore();
            std::getline(std::cin, description);
            if (description.empty())
            {
                std::cout << "Atentie! Descrierea nu poate fi goala. Incercati din nou.\n";
                std::cout << "Doriti sa reincercati pasul NUMBERINPUT? (y/n): ";
                char retryChoice;
                std::cin >> retryChoice;
                if (retryChoice == 'y' || retryChoice == 'Y')
                {
                    continue;  // Reincercam pasul TITLE
                }
                else
                {
                    // Daca utilizatorul nu vrea sa reîncerce, iesim din bucla
                    break;
                }
            }
            // Creare și adăugare pas TEXTINPUTstep în flow
            NUMBERINPUTstep* numberInputStep = new NUMBERINPUTstep();
            numberInputStep->AddDescription(description);
            flow.AddStep(numberInputStep);
            break;
        }
        case '5':
        {

            // Adaugare pas CALCULUS
            int steps;
            std::string operation;
            std::cout << "Introduceti numarul de pasi: ";
            std::cin >> steps;
            std::cout << "Introduceti operatia: ";
            std::cin.ignore();
            std::getline(std::cin, operation);


            // Utilizare template pentru a alege tipul de rezultat
            std::string resultType;
            std::cout << "Introduceti tipul de rezultat (int/float/double): ";
            std::cin >> resultType;

            if (resultType == "int")
            {
                flow.AddStep(new CALCULUSstep<int>(steps, operation));
            }
            else if (resultType == "float")
            {
                flow.AddStep(new CALCULUSstep<float>(steps, operation));
            }
            else if (resultType == "double")
            {
                flow.AddStep(new CALCULUSstep<double>(steps, operation));
            }
            else
            {
                std::cout << "Tip de rezultat necunoscut. Adaugarea pasului CALCULUS a esuat.\n";
            }

            break;
        }


        case '6':
        {
            //ADAUGARE PAS DISPLAY
            int step;
            std::string fileType;
            std::cout << "Introduceti pasul anterior: ";
            std::cin >> step;
            std::cout << "Introduceti tipul de fisier (txt/csv): ";
            std::cin >> fileType;

            DISPLAYstep displayStepObject(step,fileType);

            flow.AddStep(&displayStepObject);

            //Afisam continutul fisierului asociat pasului TEXTFILEINPUTtep sau CSVFILEINPUTStep
            displayStepObject.displayFileContent();

            break;
        }
        case '7':
        {
            // Adaugare pas TEXT FILE INPUT
            std::string description;
            std::cout << "Introduceti descrierea: ";
            std::cin.ignore();
            std::getline(std::cin, description);

            // Creeaza un obiect TEXTFILEINPUTstep
            TEXTFILEINPUTstep* textFileInputStep = new TEXTFILEINPUTstep();

            // Creare și adăugare pas TEXTIFILEINPUTstep în flow

            textFileInputStep->AddDescription(description);
            flow.AddStep(textFileInputStep);
            break;


        }
        case '8':
        {
            //Adaugare pas CSV FILE INPUT
            std::string description, fileName;
            std::cout << "Introduceti descrierea: ";
            std::cin.ignore();
            std::getline(std::cin, description);
            std::cout << "Introduceti numele fisierului: ";
            std::getline(std::cin, fileName);

            //Creeaza un obiect CSVFILEINPUTstep
            CSVFILEINPUTstep* csvFileInputStep = new CSVFILEINPUTstep();

            // Creare și adăugare pas TEXTIFILEINPUTstep în flow

            csvFileInputStep->AddDescription(description);
            flow.AddStep(csvFileInputStep);


            break;
        }

        case '9':
        {
            //Adaugare pas OUTPUT
            int step;
            std::string fileName, title, description;
            std::cout << "Introduceti pasul: ";
            std::cin >> step;
            std::cout << "Introduceti numele fisierului: ";
            std::cin.ignore();
            std::getline(std::cin, fileName);
            std::cout << "Introduceti titlul: ";
            std::getline(std::cin, title);
            std::cout << "Introduceti descrierea: ";
            std::getline(std::cin, description);
            flow.AddStep(new OUTPUTstep(step, fileName, title, description));
            break;
        }
        case '0':
            std::cout << "Iesire din crearea flow-ului.\n";
            break;
        default:
            std::cout << "Optiune invalida. Incercati din nou.\n";
        }


    }
    while (choice != '0');

    //Afiseaza timestamp-ul pentru flow-ul curent
    std::cout << "Flow creat la: " << timestamp << std::endl;




}


//functie pentru sarirea unui anumit pas
void skipFlowStep(Flow &currentFlow)
{
    std::string name;
    std::cout << "Introduceti denumirea pasului pe care doriti sa il sariti din flow: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    Step *StepToSkip = nullptr;

    //cauta pasul in flow
    for (int i = 0; i<currentFlow.GetStepsNumber(); ++i)
    {
        Step *currentStep = currentFlow.GetStep(i);
        if (currentStep->GetStepName() == name)
        {
            StepToSkip = currentStep;
            break;
        }
    }

    //verifica daca pasul a fost gasit
    if(StepToSkip == nullptr)
    {
        std::cout << "Pasul introdus nu exista in flow." << std::endl;
        return;
    }

    //afiseaza detaliile pasului pe care intentionez sa-l sar
    std::cout << "A fost eliminat din flow pasul: ";
    StepToSkip->DisplayStepInfo();


    currentFlow.skipStep(StepToSkip);

    std::cout << "Pasul a fost sarit cu succes!" << std::endl;
}

int pasiinr[100]= {0};

void CompleteFlow(Flow &currentFlow, Flow flows[], int &currentFlowIndex) //parcurge un flow
{
    int nr = currentFlow.GetStepsNumber();
    int indice = 1;
    std::vector<NUMBERINPUTstep*> inputSteps;

    currentFlow.StartFlow();




    for (int i = 0; i < nr; ++i)
    {
        // Întreabă utilizatorul dacă dorește să sara peste pasul curent
        char skipChoice;
        std::cout << "Doriti sa sariti peste pasul '" << currentFlow.GetStep(i)->GetStepName() << "'? (y/n): ";
        std::cin >> skipChoice;

        if (skipChoice == 'y' || skipChoice == 'Y')
        {
            // Utilizatorul a ales să sara peste pas, continuăm la următorul pas
            continue;
        }



        Step *currentStep = currentFlow.GetStep(i);

        // Verificăm tipul pasului
        if (dynamic_cast<TEXTINPUTstep*>(currentStep))
        {
            TEXTINPUTstep *textInputStep = dynamic_cast<TEXTINPUTstep*>(currentStep);

            // Verificăm dacă textul de input este gol
            if (textInputStep->GetTextInput().empty())
            {
                std::cout << textInputStep->GetDescription() << std::endl;
                std::string textInput;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Introduceti textul input: "<< std::endl;
                std::getline(std::cin, textInput);
                textInputStep->AddTextInput(textInput);
            }
        }
        else if (dynamic_cast<NUMBERINPUTstep*>(currentStep))
        {
            NUMBERINPUTstep *numberInputStep = dynamic_cast<NUMBERINPUTstep*>(currentStep);


            // Verificăm dacă descrierea pasului a fost setată
            if (numberInputStep->GetDescription().empty())
            {
                std::string description;
                std::cout << "Introduceti descrierea pentru pasul '" << numberInputStep->GetStepName() << "': ";
                std::cin.ignore();
                std::getline(std::cin, description);
                numberInputStep->AddDescription(description);
            }

            // Verificăm dacă numărul de input este 0 (sau altă valoare implicită)
            if (numberInputStep->GetNumberInput() == 0.0)
            {
                float numberInput;
                std::cout << "Introduceti numarul input: ";
                std::cin >> numberInput;
                pasiinr[indice++] = numberInput;
                numberInputStep->AddNumberInput(numberInput);
            }
        }
        else if (dynamic_cast<CALCULUSstep<int>*>(currentStep) ||
                 dynamic_cast<CALCULUSstep<float>*>(currentStep) ||
                 dynamic_cast<CALCULUSstep<double>*>(currentStep))
        {
            std::cout << "Doriti sa afisati acum rezultatul de la CALCULUS step? (y/n)\n";
            char op;
            std::cin >> op;

            if (op == 'y')
            {
                std::cout << "Introduceti indicii pasilor NUMBER INPUT pentru operatie:\n";
                int n1, n2;
                std::cin >> n1 >> n2;

                n1 = pasiinr[n1];
                n2 = pasiinr[n2];


                if (auto calculusStepInt = dynamic_cast<CALCULUSstep<int>*>(currentStep))
                {
                    int result = calculusStepInt->Calcul(n1, n2);
                    std::cout << "Rezultatul de la CALCULUS step este: " << result << "\n";
                }
                else if (auto calculusStepFloat = dynamic_cast<CALCULUSstep<float>*>(currentStep))
                {
                    float result = calculusStepFloat->Calcul(n1, n2);
                    std::cout << "Rezultatul de la CALCULUS step este: " << result << "\n";
                }
                else if (auto calculusStepDouble = dynamic_cast<CALCULUSstep<double>*>(currentStep))
                {
                    double result = calculusStepDouble->Calcul(n1, n2);
                    std::cout << "Rezultatul de la CALCULUS step este: " << result << "\n";
                }
                else
                {
                    std::cout << "Tipul de CALCULUS step nu este suportat.\n";
                }

            }
            else
            {
                std::cout << "Indicii pasilor NUMBER INPUT nu sunt in limitele acceptate.\n";
            }
        }




        else if (dynamic_cast<TEXTFILEINPUTstep*>(currentStep))
        {
            TEXTFILEINPUTstep *textFileInputStep = dynamic_cast<TEXTFILEINPUTstep*>(currentStep);

            // Verificăm dacă numele fișierului este gol
            if (textFileInputStep->GetFileName().empty())
            {
                std::string fileName;
                std::cout << "Introduceti numele fisierului pentru pasul '" << textFileInputStep->GetStepName() << "': ";

                // Consumăm orice caracter rezidual înainte de a solicita intrarea utilizatorului
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::getline(std::cin, fileName);
                textFileInputStep->AddFileName(fileName);
                textFileInputStep->writeParametersToFile();
            }
        }


        else if (dynamic_cast<CSVFILEINPUTstep*>(currentStep))
        {
            CSVFILEINPUTstep *csvFileInputStep = dynamic_cast<CSVFILEINPUTstep*>(currentStep);

            // Verificăm dacă numele fișierului este gol
            if (csvFileInputStep->GetFileName().empty())
            {
                std::string fileName;
                std::cout << "Introduceti numele fisierului pentru pasul '" << csvFileInputStep->GetStepName() << "': ";
                std::getline(std::cin, fileName);
                csvFileInputStep->AddFileName(fileName);

            }
        }
    }

    // Incrementarea numărului de finalizări după parcurgerea flow-ului
    bool hasErrors = (currentFlow.GetErrorScreens().size() > 0);
    if (!hasErrors)
    {
        currentFlow.CompleteFlow(hasErrors);
        std::cout << "Flow-ul '" << currentFlow.GetFlowName() << "' a fost parcurs cu succes.\n\n";
    }
    else
    {
        std::cout << "Flow-ul '" << currentFlow.GetFlowName() << "' a fost parcurs cu erori.\n\n";
    }

    // Salvarea modificărilor în vectorul de flow-uri
    flows[currentFlowIndex] = currentFlow;
}

//Functie pentru afisarea informatiilor despre un flow
void DisplayFlowInformation(const Flow& flow)
{
    std::cout << "Informatii despre flow-ul '" << flow.GetFlowName() << "':\n";
    std::cout << "Numarul total de pasi: " << flow.GetStepsNumber() << "\n";
    //sau alte informatii despre flow, cum ar fi numarul de ecrane sarite sau erori
    std::cout << "\n";
}



// Functie pentru afisarea analiticilor pentru un flow
void DisplayFlowAnalytics(const Flow& flow)
{
    std::cout << "Analitici pentru flow-ul '" << flow.GetFlowName() << "':\n";
    std::cout << "Numarul de porniri: " << flow.GetStartedCount() << "\n";
    std::cout << "Numarul de finalizari: " << flow.GetCompletedCount() << "\n";

    // Afisarea analiticilor suplimentari, cum ar fi ecranele sărite și numărul de erori
    for (const auto& pair : flow.GetSkippedScreens())
    {
        std::cout << "Numarul de sarituri pentru ecranul '" << pair.first << "': " << pair.second << "\n";
    }

    for (const auto& pair : flow.GetErrorScreens())
    {
        std::cout << "Numarul de erori pentru ecranul '" << pair.first << "': " << pair.second << "\n";
    }

    std::cout << "Numarul total de erori: " << flow.GetTotalErrors() << "\n";

    std::cout << "\n";
}


// Funcție pentru gestionarea unui flow
void ManageFlow(Flow& flow)
{
    char choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do
    {
        std::cout << "Alegeti o optiune pentru flow-ul '" << flow.GetFlowName() << "':\n";
        std::cout << "1. Afisare informatii flow\n";
        std::cout << "2. Afisare analitici flow\n";
        std::cout << "0. Intoarcere la meniul principal\n\n";
        std::cin >> choice;




        switch (choice)
        {
        case '1':
            DisplayFlowInformation(flow);
            break;
        case '2':
            DisplayFlowAnalytics(flow);
            break;

        case '0':
            std::cout << "Intoarcere la meniul principal.\n\n";
            break;
        default:
            std::cout << "Optiune invalida. Incercati din nou.\n";
        }
    }
    while (choice != '0');
}

int main()
{
    char choice;
    Flow flows[100];
    int currentFlowIndex = 0;

    do
    {
        std::cout << "Alegeti o optiune:\n";
        std::cout << "1. Creare flow nou\n";
        std::cout << "2. Parcurgere flow-uri\n";
        std::cout << "3. Gestionare flow-uri\n";
        std::cout << "4. Sarirea peste un pas\n";
        std::cout << "0. Iesire\n\n";
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            // Creare flow nou
            if (currentFlowIndex < 100)
            {
                Flow newFlow;
                CreateNewFlow(newFlow);
                flows[currentFlowIndex++] = newFlow;
                std::cout << "Flow-ul cu denumirea '" << newFlow.GetFlowName() << "' a fost creat cu succes.\n\n";
            }
            else
            {
                std::cout << "Ati atins limita maxima de fluxuri.\n";
            }
            break;
        case '2':

            // Parcurgerea unui flow după nume
            if (currentFlowIndex > 0)
            {
                std::string flowName;
                std::cout << "Introduceti numele flow-ului: ";
                std::cin >> flowName;

                // Căutăm flow-ul după nume
                Flow* foundFlow = nullptr;
                for (int i = 0; i < currentFlowIndex; ++i)
                {
                    if (flows[i].GetFlowName() == flowName)
                    {
                        foundFlow = &flows[i];
                        break;
                    }
                }

                if (foundFlow != nullptr)
                {
                    // Apelăm funcția CompleteFlow pentru a completa valorile lipsă
                    CompleteFlow(*foundFlow,flows,currentFlowIndex);
                }
                else
                {
                    std::cout << "Nu am găsit un flow cu numele specificat.\n";
                }
            }
            else
            {
                std::cout << "Nu există fluxuri disponibile.\n";
            }
            break;



        case '3':
            // Gestionare flow-uri
            if (currentFlowIndex > 0)
            {
                std::string flowName;
                std::cout << "Introduceti numele flow-ului: ";
                std::cin >> flowName;

                // Cautam flow-ul după nume
                Flow* foundFlow = nullptr;
                for (int i = 0; i < currentFlowIndex; ++i)
                {
                    if (flows[i].GetFlowName() == flowName)
                    {
                        foundFlow = &flows[i];
                        break;
                    }
                }

                if (foundFlow != nullptr)
                {
                    // Afișăm opțiunile pentru flow-ul găsit
                    ManageFlow(*foundFlow);
                }
                else
                {
                    std::cout << "Nu exista flux cu numele '" << flowName << "'.\n";
                }
            }
            else
            {
                std::cout << "Nu exista fluxuri disponibile.\n";
            }
            break;

        case '4':
            // Sarirea peste un pas
            if (currentFlowIndex > 0)
            {
                int flowIndex;
                std::cout << "Alegeti un flow (introduceti indexul): ";
                std::cin >> flowIndex;

                if (flowIndex >= 0 && flowIndex < currentFlowIndex)
                {
                    Flow &currentFlow = flows[flowIndex];
                    skipFlowStep(currentFlow);
                    std::cout << "S-a sarit peste un pas cu succes.\n";
                }
                else
                {
                    std::cout << "Indexul flow-ului este invalid.\n";
                }
            }
            else
            {
                std::cout << "Nu exista fluxuri disponibile.\n";
            }
            break;
        case '0':
            std::cout << "Iesire din program.\n";
            break;
        default:
            std::cout << "Optiune invalida. Incercati din nou.\n";
        }
    }
    while (choice != '0');

    return 0;
}








