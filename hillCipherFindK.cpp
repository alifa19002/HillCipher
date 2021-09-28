/*
Anggota Kelompok:
- Cut Fazira Zuhra (140810190010)
- Alifa Hafida Anwar (140810190018)
- Putri Ainur Fitri (140810190052)
Kriptografi - Program Hill Cipher
*/

#include<iostream>
#include<bits/stdc++.h> 
using namespace std;

string hapusSpasi(string str){ //menghapus spasi
    int count = 0; 
    for (int i = 0; str[i]; i++) 
        if (str[i] == ' ') 
            str[i] = 'X';
	return str;
}

int inversKey[2][2];

void inversMatriks(int key[2][2]) {
	int tempKey[2][2];
	tempKey[0][0]=(int)(key[1][1]);
	tempKey[0][1]=(int)((-1) * key[0][1]);
	tempKey[1][0]=(int)((-1) * key[1][0]);
	tempKey[1][1]=(int)(key[0][0]);
	int determinan = (key[0][0]*key[1][1]) - (key[0][1]*key[1][0]);
	int inversDet = 0;
    int flag = 0;
    for (int i = 0; i < 26; i++){
        flag = (determinan * i) % 26;
        if (flag < 0){
        	flag = flag + 26;
		}
        if (flag == 1){
            inversDet = i;
        }
    }
	for(int i=0 ; i<2 ; i++)
		for(int j=0 ; j<2 ; j++){
			if ( tempKey[i][j] < 0 ) {
				int tempNumber = tempKey[i][j]*inversDet;
			    inversKey[i][j] = ((tempNumber%26) + 26)%26;
			}
			else{
				inversKey[i][j] = (tempKey[i][j]*inversDet%26);
			}
		}
}

string Enkripsi(string plain, int key[2][2]) {
	string cipher = "";
	int stringLength = plain.length();  //panjang plainteks
	if (plain.length()%2==1)
		stringLength += 1;      //jika panjang teksnya ganjil, maka panjang teks ditambah 1
	char plainMatrix[2][stringLength];
	int count=0;
	for(int i=0; i<stringLength/2;i++)
		for(int j=0;j<2;j++){
			if(plainMatrix[j][i] == 32){
				break;
			}
			plainMatrix[j][i] = plain[count];
			count++;
		}
	for(int i = 0; i < stringLength/2; i++){
   		for(int j = 0; j < 2; j++){
   			int tempCipher=0;
   			for(int k = 0; k < 2; k++){
   				int l = key[j][k] * (plainMatrix[k][i]%65); //kalikan ke key
   				tempCipher += l;	
			}
			tempCipher = (tempCipher%26) +65;   //matriks mod 26
			cipher += (char)tempCipher;	
		   }
	}
	return cipher;
}

string Dekripsi(string cipher, int key[2][2]) {
	string plain = "";
	int stringLength = cipher.length();
	if (plain.length()%2==1)
		stringLength = cipher.length()+1;
   	inversMatriks(key);
   	char cipherMatriks[2][stringLength/2];
	int count=0;
	for(int i=0; i<stringLength/2;i++)
		for(int j=0;j<2;j++){
			cipherMatriks[j][i] = cipher[count];
			count++;
		}
	
	for(int i = 0; i < cipher.length()/2; i++){
   		for(int j = 0; j < 2; j++){
   			int tempPlain=0;
   			for(int k = 0; k < 2; k++){
   				int l = inversKey[j][k] * (cipherMatriks[k][i]%65);
   				tempPlain += l;
			   }
			tempPlain = (tempPlain%26) +65;
			plain += (char)tempPlain;	
		   }
	}
	return plain;
}

int gcd(int m, int n){
	if (n > m)
		swap(m,n);
	
	do{
		int temp = m % n;
		m = n;
		n = temp;
	} while (n != 0);
	
	return m;
}

int mencariInvers(int m, int n){
	int t0 = 0,t1 = 1,invers,q,r,b = m;
	while(r != 1){
		q = m/n;
		r = m%n;
		invers = t0 - q * t1;
		if(invers < 0){
			invers = b - (abs(invers)%b);
		}else{
			invers %= b;
		}
		t0 = t1;
		t1 = invers;
		m = n;
		n = r;	
	}
	return invers;
}


void mencariKey(){
	//deklarasi
	string plainteks,cipherteks;
	int key[2][2],det,detInv,adj[2][2],invPlainteks[2][2],plainMatrix[2][2],cipMatrix[2][2],counter;
	int p,c;
	int transpose[2][2];
	
	//input plainteks
	cout << "Masukkan Plainteks : ";
	cin.ignore();
	getline(cin,plainteks);
	
	//assign plainteks ke plainMatrix
	counter = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			p = toupper(plainteks[counter]) - 65;
			plainMatrix[i][j] = p;
			counter++;
		}
	}
	
	//input cipherteks
	cout << "Masukkan Cipherteks : ";
	getline(cin,cipherteks);
	
	//assign cipherteks ke cipMatrix
	counter = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			c = toupper(cipherteks[counter]) - 65;
			cipMatrix[i][j] = c;
			counter++;
		}
	}
	
	// determinan
	det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
	if(gcd(det,26)==1){
		// inverse dari determinan mod 26
		detInv = mencariInvers(26,det);
		
		//menghitung adjoin
		adj[0][0] = plainMatrix[1][1];
		adj[0][1] = (-1)*plainMatrix[0][1];
		adj[1][0] = (-1)*plainMatrix[1][0];
		adj[1][1] = plainMatrix[0][0];
		
		//menghitung matriks invers dari plainteks
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				invPlainteks[i][j] = detInv * adj[i][j];
				if(invPlainteks[i][j] < 0){
					invPlainteks[i][j] = 26 - (abs(invPlainteks[i][j])%26); 
				}else{
					invPlainteks[i][j] = invPlainteks[i][j];
					invPlainteks[i][j] = invPlainteks[i][j] % 26;
				}
			} 
		}
		
		//Search key
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				key [i][j] = 0;
				for(int k = 0; k < 2; k++){
					key [i][j] += (invPlainteks[i][k] * cipMatrix[k][j]);
				}
				key [i][j] %= 26;
			}
		}
		

		for (int i = 0; i < 2; i++){
    	for (int j = 0; j < 2; j++){
      		transpose[j][i] = key[i][j];
    		}
  		}
  	
	    for(int i = 0; i < 2; i++){
	        for (int j = 0; j < 2; j++){
	            cout << (transpose[i][j]) << "\t";
	        }
	        cout <<endl;
	    } 	 	
	}else{
		cout << "Determinan tidak relatif " <<endl;
		cout << "Key tidak ditemukan" <<endl<<endl;
	}
}

int main(){
	int key[2][2], pilihan;
    string plain, cipher;
    // menentukkan matriks key
	key[0][0] = 3;
	key[0][1] = 2;
	key[1][0] = 2;
	key[1][1] = 7;
	do{
        // Pilihan Menu
		cout << "============================================" << endl;
        cout << "==========[ PROGRAM HILL CIPHER 2X2 ]=======" << endl;
        cout << "============================================" << endl;
		cout << "MENU:" <<endl;
		cout << "1. Enkripsi" <<endl;
		cout << "2. Dekripsi" <<endl;
		cout << "3. Mencari Key" <<endl;
		cout << "4. Keluar" <<endl;
		cout << "Pilih : "; cin >> pilihan;
		switch(pilihan){
			case 1:
				cout << "\nMasukkan Plainteks: ";
				cin.ignore();
				getline(cin,plain);
				plain = hapusSpasi(plain); 
				transform(plain.begin(), plain.end(), plain.begin(), ::toupper); //mengubah huruf menjadi kapital
				cout << "Ciphertext : " << Enkripsi(plain,key) <<endl<<endl; //hasil enkripsi
				break;
			case 2:
				cout << "\nInput Ciphertext: ";
				cin.ignore();
				getline(cin,cipher);
				cipher = hapusSpasi(cipher);
				transform(cipher.begin(), cipher.end(), cipher.begin(), ::toupper); 
				cout << "Plaintext : " << Dekripsi(cipher,key) <<endl<<endl;
				break;
			case 3:
				cout<<endl;
				mencariKey();
				break;
			case 4:
				break;
			default:
				cout << "\nPilihan yang anda masukkan salah!" <<endl;
                cout << "Pilihan hanya tersedia dari 1-4" <<endl;
				break;
		}
	}while(pilihan!=4);
}
