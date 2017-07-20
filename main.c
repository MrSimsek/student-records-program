#include <stdio.h>
#include <stdlib.h>

struct studentData {
	int studNum;
	char lastName[ 15 ];
	char firstName[ 10 ];
	double grade;
};

void createFile ( FILE *fPtr );
void updateFile ( FILE *fPtr );
void textFile ( FILE *readPtr );
void printFile ( FILE *fPtr );

int main( void ) {
	
	FILE *cfPtr;
	
	createFile( cfPtr ); // Creates "class.dat" file.
	updateFile( cfPtr ); // Adds records to "class.dat" file.
	printFile( cfPtr ); // Prints the data in "class.dat"
	textFile( cfPtr ); // Copies all the data in "class.dat" into "students.txt"
	
	printf("\n");
	
	system("PAUSE");
	return 0;
}

void createFile ( FILE *fPtr ){
	
	int i;
	
	struct studentData blankStudent = { 0, "", "", 0.0 };
	
	if( (fPtr = fopen("class.dat", "w")) == NULL ){
		printf("File could not be opened.\n");
	}
	else{
		for( i = 1; i <= 10; i++ ){
			fwrite( &blankStudent, sizeof( struct studentData ), 1, fPtr );
		}
		
		fclose( fPtr );
	}
}

void updateFile ( FILE *fPtr ){
	
	struct studentData student = { 0, "", "", 0.0 };
	
	if( ( fPtr = fopen("class.dat", "rb+")) == NULL ){
		printf("File could not be opened.\n");
	}
	else{
		
		printf("Enter student number (1 to 10, 0 to end input).\n? ");
		scanf("%d", &student.studNum);
		
		while( student.studNum != 0 ){
			
			printf("Enter lastname, firstname and grade of the student\n? ");
			
			fscanf( stdin, "%s%s%lf", student.lastName, student.firstName, &student.grade);
			
			fseek( fPtr, ( student.studNum - 1) * sizeof( struct studentData ), SEEK_SET );
			
			fwrite( &student, sizeof( struct studentData ), 1, fPtr );
			
			printf("Enter the student number.\n? ");
			scanf("%d", &student.studNum);
		}
		
		fclose( fPtr );
	}
}

void textFile( FILE *readPtr ){
	
	readPtr = fopen("class.dat","rb+");
	
	FILE *writePtr;
	
	struct studentData student = { 0, "", "", 0.0 };
	
	if( ( writePtr = fopen("students.txt", "w") ) == NULL ){
		printf("File could not be opened.\n");
	}
	else{
		rewind( readPtr );
		fprintf( writePtr, "%-6s%-16s%-11s%10s\n", "Std#", "Last Name", "First Name", "Grade" );
		
		while( !feof( readPtr ) ){
			fread( &student, sizeof( struct studentData ), 1, readPtr );
			
			if( student.studNum != 0 ){
				fprintf( writePtr, "%-6d%-16s%-11s%10.2f\n", student.studNum, student.lastName, student.firstName, student.grade );
			}
		}
		
		fclose( writePtr );
	}
}

void printFile( FILE *fPtr ){
	
	struct studentData student = { 0, "", "", 0.0 };
	
	if( ( fPtr = fopen("class.dat", "rb") ) == NULL ){
		printf("File could not be opened.\n");
	}
	else{
		printf("%-6s%-16s%-11s%10s\n", "Std#", "Last Name", "First Name", "Grade");
		
		while( !feof( fPtr ) ){
			fread( &student, sizeof( struct studentData ), 1, fPtr );
			
			if( student.studNum != 0 ){
				printf("%-6d%-16s%-11s%10.2f\n", student.studNum, student.lastName, student.firstName, student.grade);
			}
		}
		
		fclose( fPtr );
	}
}
