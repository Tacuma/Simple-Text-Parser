//Tacuma Solomon
//@02580808
//Data Communications
//February 6th 2012
//Prep. Assignment


#include <stdio.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
	
	if (argc != 5){ //checks to see if the number of arguments was correct
		printf("Incorrect number of arguments inserted.\n");
		return 0;
	}
	else {
		int start = atoi(argv[3]);
		int end = atoi(argv[4]);
		
		//opens input file
		int in = open(argv[1], O_RDONLY);
		if (in==-1){
			fprintf(stderr, "Error. Can't open input file %s \n", argv[1]);
			return 0;
		}

		//opens output file
		int out = open(argv[2], O_WRONLY);
		if (out == -1) {
  			fprintf(stderr, "Error. Can't open output file %s\n", argv[2]);
		        return 0;
		}

		//ensures end number is always greater than start number
		if (start>end){
			fprintf(stderr, "Error. End value should not be smaller than start value \n");
			return 0;
		}

		int checkspace=0;
		int count=0;
		char x[1];
	
         	//extracts chars from the input file
		while(read(in,x,1)){
			//This the program iterates through the characters till it gets to the first word
			if (!((x[0]==32)||(x[0]==10)||(x[0]==12)||(x[0]==9))){   //If the character is in a word ...
			    checkspace=0;					 //The checkspace is 0	
			}		
			if (((x[0]==32)||(x[0]==10)||(x[0]==12)||(x[0]==9)) && (checkspace==0)){  
			//If there is a space, linefeed, carriage return or tab, and the previous byte read was a character..
			    checkspace=1; 
			    count++;  //increase count
			}
			if (count == (start-1)){ //The word is found and printing to the output file begins here
				while(read(in,x,1)){
					if (!((x[0]==32)||(x[0]==10)||(x[0]==12)||(x[0]==9))){ //If the character is in a word ...
			    			checkspace=0;				       //The checkspace is 0
						write(out, x, 1);
					}
					if (((x[0]==32)||(x[0]==10)||(x[0]==12)||(x[0]==9)) && (checkspace==0)){
					//If there is a space, linefeed, carriage return or tab, and the previous byte read was a character..
			   			 checkspace=1;
					         write(out, x, 1); //write to output file
			   			 count++; //increase count
					}
					if (count == end){
						break;
					}
				}
			}				
		} 
		close(in);	//close file
	}
	return 0;
}
