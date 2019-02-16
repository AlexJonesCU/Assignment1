#include <iostream>
#include <string>
#include <fstream> //source: http://www.cplusplus.com/doc/tutorial/files/
#include <math.h> //source: http://www.cplusplus.com/reference/cmath/sqrt/

using namespace std;

string yesOrNo;
int sum = 0;
int meanSum = 0;
float counter = 0.0; //not proper practice to put these up here, but we cant use arrays which would make this code more OO and proper practice
float mean = 0.0;
float variance = 0.0;
float topVar = 0.0;
float topTot = 0.0;
float stanDev = 0.0;
int countA = 0, countC = 0, countG = 0, countT = 0;
float relProbA = 0.0, relProbC = 0.0, relProbG = 0.0, relProbT = 0.0;
float totalNucleotides = 0.0;
float totalBigrams = 0.0;
int countAA = 0, countAC = 0, countAG = 0, countAT = 0;
int countCA = 0, countCC = 0, countCG = 0, countCT = 0;
int countGA = 0, countGC = 0, countGG = 0, countGT = 0;
int countTA = 0, countTC = 0, countTG = 0, countTT = 0;
float bigProbAA = 0.0, bigProbAC = 0.0, bigProbAG = 0.0, bigProbAT = 0.0;
float bigProbCA = 0.0, bigProbCC = 0.0, bigProbCG = 0.0, bigProbCT = 0.0;
float bigProbGA = 0.0, bigProbGC = 0.0, bigProbGG = 0.0, bigProbGT = 0.0;
float bigProbTA = 0.0, bigProbTC = 0.0, bigProbTG = 0.0, bigProbTT = 0.0;
string strand;
float theMean(int sum, float counter);
float calculateVariance(float mean, string fileName, int counter);
float standardDeviation(float variance);
int DNAStringGenerator(string nucleotides);
int BigramCounter(string bigrams);
string GaussianDistribution(float mean, float stanDev);


int main(int argc, char ** argv)
{
  do
  {
    string fileName;
    string line;
    int count;
    cout << "What is the name of the text file that has the list of DNA strings?: ";
    cin >> fileName;
    ifstream readFile (fileName); //source : http://www.cplusplus.com/reference/fstream/ifstream/
    if (readFile.is_open())
    {
      cout << "The DNA strands are: " << endl;
      while (getline (readFile,line)) //reads each line in file as long as file is open
      {
        cout << line << '\n';
        count = line.length() - 1; //count is length of the string in that line
        sum += count;

        ++counter; //adds one to counter then returns to determine
        // how many strands of DNA there are in the file

        DNAStringGenerator(line);
        BigramCounter(line);

      }

      theMean(sum, counter);  //withing is_open() so will only run if file opens
      calculateVariance(mean, fileName, counter);
    }

    GaussianDistribution(mean, stanDev);

    ofstream outFile;
    outFile.open("AlexJones.txt");
    if (outFile.is_open())
    {
      outFile << "Alex Jones" << endl;
      outFile << "2290441" << endl;
      outFile << "aljones@chapman.edu" << endl;
      outFile << "CPSC 350-02" << endl;
      outFile << "Assignment # 1" << endl;
      outFile << endl;

      outFile << "Statistics" << endl;
      outFile << "----------" << endl;
      outFile << "Sum: " << sum << endl;
      outFile << "Mean: " << mean << endl;
      outFile << "Variance: " << variance << endl;
      outFile << "Standard Deviation: " << stanDev << endl;
      outFile << endl;
      outFile << "Relative Probability of A: " << relProbA << endl;
      outFile << "Relative Probability of C: " << relProbC << endl;
      outFile << "Relative Probability of G: " << relProbG << endl;
      outFile << "Relative Probability of T: " << relProbT << endl;
      outFile << endl;
      outFile << "bigram probability of AA: " << bigProbAA << endl;
      outFile << "bigram probability of AC: " << bigProbAC << endl;
      outFile << "bigram probability of AG: " << bigProbAG << endl;
      outFile << "bigram probability of AT: " << bigProbAT << endl;
      outFile << "bigram probability of CA: " << bigProbCA << endl;
      outFile << "bigram probability of CC: " << bigProbCC << endl;
      outFile << "bigram probability of CG: " << bigProbCG << endl;
      outFile << "bigram probability of CT: " << bigProbCT << endl;
      outFile << "bigram probability of GA: " << bigProbGA << endl;
      outFile << "bigram probability of GC: " << bigProbGC << endl;
      outFile << "bigram probability of GG: " << bigProbGG << endl;
      outFile << "bigram probability of GT: " << bigProbGT << endl;
      outFile << "bigram probability of TA: " << bigProbTA << endl;
      outFile << "bigram probability of TC: " << bigProbTC << endl;
      outFile << "bigram probability of TG: " << bigProbTG << endl;
      outFile << "bigram probability of TT: " << bigProbTT << endl;
      outFile << endl;
      outFile << "More DNA strings: " << strand << endl;

      cout << "The data has been written to the 'AlexJones' text file'" << endl;
      outFile.close();
      readFile.close();
      cout << "Do you want to use data from another file? (yes or no): ";
      cin >> yesOrNo;
    }
  }
  while(yesOrNo == "yes");

  return 0;
}


float theMean(int sum, float counter)
{
  mean = sum / counter;
  return mean;
}

float calculateVariance(float mean, string fileName, int counter)
{
  string theLine; //different local variable.. could have the same name as above
  int theCount;
  ifstream readSameFileAgain (fileName);
  while (getline (readSameFileAgain, theLine)) //reads each line in file as long as file is open
  {
    theCount = theLine.length() - 1;
    topVar = (theCount - mean) * (theCount - mean);
    topTot += topVar;//total top
  }
  variance =  topTot / (counter - 1);//counter can be used since it is a global variable in this program

  standardDeviation(variance);
  return variance;
}

float standardDeviation(float variance)
{
  stanDev = sqrt (variance);
  return stanDev;
}

int DNAStringGenerator(string nucleotides)
{
  int total = 0;
  //totalNucleotides += (nucleotides.length() - 1);
  for (unsigned i = 0; i < nucleotides.length(); ++i) //source: http://www.cplusplus.com/reference/string/string/at/
  {
    total = nucleotides.length() - 1; //count is length of the string in that line

    if (nucleotides.at(i) == 'A')
    {
      countA++;
    }
    else if (nucleotides.at(i) == 'C')
    {
      countC++;
    }
    else if (nucleotides.at(i) == 'G')
    {
      countG++;
    }
    else if (nucleotides.at(i) == 'T')
    {
      countT++;
    }
  }
  totalNucleotides += total;

  relProbA = countA/totalNucleotides;
  relProbC = countC/totalNucleotides;
  relProbG = countG/totalNucleotides;
  relProbT = countT/totalNucleotides;

  return 0;
}

int BigramCounter(string bigrams)
{
  int total = 0;
  //totalNucleotides += (nucleotides.length() - 1);
  for (unsigned i = 0; i < bigrams.length(); ++i) //source: http://www.cplusplus.com/reference/string/string/at/
  {
    total = bigrams.length() - 1; //count is length of the string in that line
    if (i % 2 == 0) //if i is even meaning it counts the bigrams i pairs with every even i
    {
      if (bigrams.at(i) == 'A')
      {
        if (bigrams.at(i + 1) == 'A')
        {
          countAA++;
        }
        else if (bigrams.at(i + 1) == 'C')
        {
          countAC++;
        }
        else if (bigrams.at(i + 1) == 'G')
        {
          countAG++;
        }
        else if (bigrams.at(i + 1) == 'T')
        {
          countAT++;
        }
      }
      else if (bigrams.at(i) == 'C')
      {
        if (bigrams.at(i + 1) == 'A')
        {
          countCA++;
        }
        else if (bigrams.at(i + 1) == 'C')
        {
          countCC++;
        }
        else if (bigrams.at(i + 1) == 'G')
        {
          countCG++;
        }
        else if (bigrams.at(i + 1) == 'T')
        {
          countCT++;
        }
      }
      else if (bigrams.at(i) == 'G')
      {
        if (bigrams.at(i + 1) == 'A')
        {
          countGA++;
        }
        else if (bigrams.at(i + 1) == 'C')
        {
          countGC++;
        }
        else if (bigrams.at(i + 1) == 'G')
        {
          countGG++;
        }
        else if (bigrams.at(i + 1) == 'T')
        {
          countGT++;
        }
      }
      else if (bigrams.at(i) == 'T')
      {
        if (bigrams.at(i + 1) == 'A')
        {
          countTA++;
        }
        else if (bigrams.at(i + 1) == 'C')
        {
          countTC++;
        }
        else if (bigrams.at(i + 1) == 'G')
        {
          countTG++;
        }
        else if (bigrams.at(i + 1) == 'T')
        {
          countTT++;
        }
      }
    }
  }

  totalBigrams += total/2;

  bigProbAA = countAA/totalBigrams;
  bigProbAC = countAC/totalBigrams;
  bigProbAG = countAG/totalBigrams;
  bigProbAT = countAT/totalBigrams;
  bigProbCA = countCA/totalBigrams;
  bigProbCC = countCC/totalBigrams;
  bigProbCG = countCG/totalBigrams;
  bigProbCT = countCT/totalBigrams;
  bigProbGA = countGA/totalBigrams;
  bigProbGC = countGC/totalBigrams;
  bigProbGG = countGG/totalBigrams;
  bigProbGT = countGT/totalBigrams;
  bigProbTA = countTA/totalBigrams;
  bigProbTC = countTC/totalBigrams;
  bigProbTG = countTG/totalBigrams;
  bigProbTT = countTT/totalBigrams;

  return 0;
}

string GaussianDistribution(float mean, float stanDev)
{
  //const string DNA = "ACGT";
  string spot;
  float c, d;
  int a = rand() % 2; // 0 or 1
  int b = rand() % 2;

  c = (sqrt(-2 * log(a)) * cos(2 * M_PI * b)); //source: https://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c
  d = stanDev * c + mean;

//  srand()
  for (int i = 0; i <= 1000; i++) // makes 1000 random strings
  {

    for (int j = 0; j <= mean; j++) // second loop for length of the string based on average of previous string lengths
    {
      int one = rand() % 4;
      if (one == 0)
      {
        spot = "A"; //appends to end
      }
      else if (one == 1)
      {
        spot = "C";
      }
      else if (one == 2)
      {
        spot = "G";
      }
      else if (one == 3)
      {
        spot = "T";
      }
      strand += spot;
    }
  }
  return strand;
}
