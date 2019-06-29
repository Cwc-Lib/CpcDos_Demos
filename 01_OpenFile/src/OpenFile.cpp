#include <GZE.h>
#include <Main>

#include <CpcDos/WindowsHeader.h> //Windows.h


gzUIntX  nFileSize = 0;
gzUInt8* aFileData = (gzUInt8*)&nFileSize; //Set to empty data -> To be compatible with printf("%s");

gzBool fWindows_LoadFile(gzUInt8* _sFullPath){

   FILE*  f = fopen((char*)(gzUInt8*)_sFullPath, "rb+");

	if (f != NULL){

		WIN32_FILE_ATTRIBUTE_DATA fa;
		long lSize;
		fseek (f , 0 , SEEK_END);
		lSize = ftell (f);
		rewind (f);

		gzUIntX _nSize = lSize;
		
		printf("Load file: %s  :  Size:%d \n", _sFullPath, _nSize);

		gzUInt8* _aData = new gzUInt8[_nSize + 1];
		fread(_aData, 1, _nSize, f);
		_aData[_nSize] = 0; //To be compatible with printf("%s");

		nFileSize = _nSize;
		aFileData = _aData;

		fclose(f);
		return true;

	}else{
		
		printf("Error, can't open file : %s \n", _sFullPath);
		fclose(f);
		return false;
	 }
}


gzBool fCpcDos_LoadFile(gzUInt8* _sFullPath){

		gzUInt _nExist = CpcDos->File_exist((char*) _sFullPath);
		if(_nExist > 0){
		
		   nFileSize =  CpcDos->File_size((char*) _sFullPath);
		   aFileData = new gzUInt8[nFileSize + 1];
		   
		   	printf("Load file: %s  :  Size:%d \n", _sFullPath, nFileSize);

			CpcDos->File_read_all((char*)_sFullPath, (char*)"RB", (char*)aFileData);
			aFileData[nFileSize] = 0; //To be compatible with printf("%s");

		}else{
			
			printf("File not found: %s \n", _sFullPath);
			return false;
		}

	return true;
}


gzInt Main(gzText8 _sArg, gzUIntX _nId, gzInt _nCmd){

	if(bOnCpcDos){
		fCpcDos_LoadFile((gzUInt8*)"Info.txt");
	}else{
		fWindows_LoadFile((gzUInt8*)"Info.txt");
	}

	printf("%s", aFileData);
	
	
	return 1; // 1 Still Alive, 0 Stop, < 0 Errors
}


gzInt Update(){
	static gzInt _nCount = 0;
	static gzInt _nAnim = 0;
	
	switch(_nAnim){
		case 0:
			printf("\b \\ \r");
		break;
		case 1:
			printf("\b | \r");
		break;
		case 2:
			printf("\b / \r");
		break;
		case 3:
			printf("\b - \r");
		break;
		case 4:
			printf("\b \\ \r");
		break;
		case 5:
			printf("\b | \r");
		break;
		case 6:
			printf("\b / \r");
		break;
		case 7:
			printf("\b - \r");
		break;
	}

	// _nCount++;
	// if(_nCount > 4){
		// _nCount = 0;
		_nAnim++;
		if(_nAnim > 7){_nAnim = 0;}
	// }
	
	
	Sleep(100);
	
	// if(bOnCpcDos)
		// CpcDos->sleep(30000); // milliseconds cpcdos
	// else
		// usleep(10000); // Milliseconds windows

	
	return 1; // 1 Still Alive, 0 Stop, < 0 Errors
}

gzInt Close(gzInt _nExitCode){
	
	delete aFileData;
	
	printf("Good bye: %d \n", _nExitCode);
	return  _nExitCode; //Success
}



