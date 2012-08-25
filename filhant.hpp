			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "Fil hant.hpp"							//
			//														//
			//			F�rfattad av: Andreas Sehr 2002,01,19		//
			//														//
			//			Senast �ndrad:	2002,04,16					//
			//														//
			//////////////////////////////////////////////////////////

class SaveFile {
	public:
		SaveFile();
		~SaveFile();
		bool open(char*);
		char* get(char*);
	private:
		ifstream inFil;
		String* returnString;
		String* stringOfFile;
		bool fileIsOpen;

};

SaveFile::SaveFile()
{
	stringOfFile = new String("");
	returnString = new String("");
}

SaveFile::~SaveFile()
{
	delete stringOfFile;
	delete returnString;

	if (fileIsOpen)
	{
		inFil.clear();
		inFil.close();
	}
}

bool SaveFile::open(char* initFile)
{
	inFil.open(initFile);
	if(inFil.fail())
	{
		fileIsOpen = false;
		return false;
	}
	else
	{
		fileIsOpen = true;
		char ch;
		for (int i = 0; !inFil.eof(); ++i)
		{
			if (inFil.get(ch))				//Kopierar filen tilll ett str�ng objekt
				*stringOfFile += ch;		//som �r l�ttare att hantera
		}
		return true;
	}
}

char* SaveFile::get(char* initGet)
{
	ofstream fout("res.txt");
	fout << stringOfFile->getString();

	if (fileIsOpen)
	{
		String testString("");
		returnString->setToNull();

		bool beginTest = false, copyString = false, endTest = false;

		for (int i=0; i < stringOfFile->getLen(); ++i) //G�r igenom str�ng objektet tecken f�r tecken
		{
			fout << "\n" << i << "\n";
			fout << "beginTest = ";
			if (beginTest == true)
				fout << "true" << endl;
			else
				fout << "false" << endl;

			fout << "copyString = ";
			if ( copyString == true)
				fout << "true" << endl;
			else
				fout << "false" << endl;

			fout << "endTest = ";
			if (endTest == true)
				fout << "true" << endl;
			else
				fout << "false" << endl;


			if (stringOfFile[0][i] == ']')
			{
				if (testString == initGet)
				{
					if (beginTest == true)
						copyString = true;
					else if (endTest == true)
						copyString = false;
				}
				beginTest = false;
				endTest = false;
				testString.setToNull();			//Nollst�ller testString
				continue;
			}
			if (beginTest == true)
				testString += stringOfFile[0][i];

			if (stringOfFile[0][i] == '[')
			{
				if (stringOfFile[0][i+1] == '/')
				{
					endTest = true;
					copyString = false;
				}
				else
					beginTest = true;
			}

			if (copyString == true)
			{
				*returnString += stringOfFile[0][i];		//L�gga till tecken f�r tecken till
			}									//det str�ngobjekt som retureras
		}
		fout << "\n\n" << returnString->getString() << endl;
		fout << "\n" << returnString->getLen() << endl;
		return returnString->getString();
	}
}