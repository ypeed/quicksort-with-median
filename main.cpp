#include <iostream>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#include <vector> 


using namespace std;

void izpis(vector<int> &array, int n){
    for(int i=0; i<n; i++){
        cout << array[i] << " ";
    }
}

//NARASCUJOCE
int deli_narascujoce(vector<int> &array, int dno, int vrh){
    //swap -------------------
    int mid = (dno+vrh) / 2;
    int temp = array[dno];
    array[dno] = array[mid];
    array[mid] = temp;
    //------------------------
    int w = array[dno];                                //
    int i = dno+1;
    int j = vrh;
    while(true){
        while(array[j] >= w && j >= dno+1){
            j--;
        }
        while(array[i] < w && i <= vrh-1) {
            i++;
        }
        if(i < j){
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }else{
            int temp = array[j];
            array[j] = array[dno];
            array[dno] = temp;
            return j;
            break;
        }
    }

}

void uredi_narascujoce(vector<int> &array, int dno, int vrh){
    if(dno < vrh){
        int j = deli_narascujoce(array, dno, vrh);
        uredi_narascujoce(array, dno, j-1);
        uredi_narascujoce(array, j+1, vrh);
    }
}

//PADAJOCE
int deli_padajoce(vector<int> &array, int dno, int vrh){
    //swap -------------------
    int mid = (dno+vrh) / 2;
    int temp = array[vrh];
    array[vrh] = array[mid];
    array[mid] = temp;
    //------------------------
    int w = array[vrh];
    int i = vrh-1;
    int j = dno;
    while(true){
        while(array[j] >= w && j <= vrh-1){
            j++;
        }
        while(array[i] < w && i >= dno+1) {
            i--;
        }
        if(i > j){
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }else{
            int temp = array[j];
            array[j] = array[vrh];
            array[vrh]= temp;
            return j;
            break;
        }
    }

}

void uredi_padajoce(vector<int> &array, int dno, int vrh){
    if(dno < vrh){
        int j = deli_padajoce(array, dno, vrh);
        uredi_padajoce(array, dno, j-1);
        uredi_padajoce(array, j+1, vrh);
    }
}


void uredi_obstojeco(vector<int> &array, int n){
    int dno = 0;
    int vrh = n-1; 
    uredi_narascujoce(array, dno, vrh);
}

//GENERIRAJ
void generiraj_random(vector<int> &array, int n){
    array.clear();
    for(int i=0; i<n; i++){
        array.push_back(rand()%1000+1);
    }
}

void generiraj_narascujoce(vector<int> &array, int n){
    generiraj_random(array,n);
    int dno = 0;
    int vrh = n-1; 
    uredi_narascujoce(array, dno, vrh);
}

void generiraj_padajoce(vector<int> &array,int n){
    generiraj_random(array,n);
    int dno = 0;
    int vrh = n-1;
    uredi_padajoce(array, dno, vrh);
}

//PREVERJANJE
bool preveri_narascujoce(vector<int> &array, int n){
    for(int i=0; i<n-1; i++){
        if(array[i] > array[i+1]){
            return false;
        }
    }
    return true;

}

bool preveri_padajoce(vector<int> &array, int n){
    for(int i=0; i<n-1; i++){
        if(array[i] < array[i+1]){
            return false;
        }
    }
    return true;

}

int main()
{
    srand(time(NULL));
    bool running = true;
    int izbira;
    int n;
    vector<int> array;

    clock_t start, finish;
    double duration;

    cout << "Hitro uredi – izbira: " << endl;
    cout << "\n1 Generiraj nakljucno zaporedje" << endl;
    cout << "2 Generiraj urejeno narascajoce zaporedje" << endl;
    cout << "3 Generiraj urejeno padajoce zaporedje" << endl;
    cout << "4 Izpis zaporedja" << endl;
    cout << "5 Uredi" << endl;
    cout << "6 Konec" << endl;

    while(running){
        cout << "\nVasa izbira: " << endl;
        cin >> izbira;
        switch(izbira){
        //GENERIRANJE
        case 1:
            cout << "Vpisi velikost zaporedja: " << endl;
            cin >> n;
            generiraj_random(array, n);
            if(n <= 1000){
                cout << "NOVO zaporedje generirano: ";
                izpis(array, n);
            }else{
                cout << "NOVO zaporeje generirano, preveliko za izpis" << endl;
            }
            break;

        //NARASCUJOCE
        case 2:
            cout << "NARASCUJOCE ZAPOREDJE: " << endl;
            cout << "Vpisi velikost zaporedja: " << endl;
            cin >> n;
            start = clock();  // zacnemo miriti cas
            generiraj_narascujoce(array, n);
            finish = clock(); // koncamo z meritvijo
            duration = (double) (finish - start)/ CLOCKS_PER_SEC;
            cout << "NOVO zaporedje generirano => ";

            //preverjanje
            if(preveri_narascujoce(array, n)){
                cout << "USPESNO UREJENO ZAPOREDJE" << endl;
            }else{
                cout << "NAPAKA: ZAPOREDJE NI UREJENO NARASCUJOCE" << endl;
            }

            //ce je zaporeje malo ga tudi izpisemo
            if(n <= 1000){
                cout << "Zaporedje: " << endl;
                izpis(array, n);
            }
            cout << endl;
            cout << "Cas izvajanje => " << duration << "s" << endl;
            break;

        //PADAJOCE
        case 3:
            cout << "PADAJOCE ZAPOREDJE: " << endl;
            cout << "Vpisi velikost zaporedja: " << endl;
            cin >> n;
            start = clock();
            generiraj_padajoce(array, n);
            finish = clock();
            duration = (double) (finish - start)/ CLOCKS_PER_SEC;
            cout << "NOVO zaporedje generirano => ";

            //preverjanje
            if(preveri_padajoce(array, n)){
                cout << "USPESNO UREJENO ZAPOREDJE" << endl;
            }else{
                cout << "NAPAKA: ZAPOREDJE NI UREJENO PADAJOCE" << endl;
            }

            if(n <= 1000){
                cout << "Zaporedje: " << endl;
                izpis(array, n);
            }
            cout << endl;
            cout << "Cas izvajanje => " << duration << "s" << endl;
            break;

        //IZPIS
        case 4:
            if(n <= 1000){
                cout << "Izpis zaporedja: ";
                izpis(array, n);
            }else{
                cout << "Zaporedje je preveliko..." << endl;
            }
            break;

        //UREJANJE
        case 5: 
            cout << "Zaporedje urejeno => ";
            start = clock();
            uredi_obstojeco(array, n);
            finish = clock();
            duration = (double) (finish - start)/ CLOCKS_PER_SEC;

            if(preveri_narascujoce(array, n)){
                cout << "USPESNO UREJENO ZAPOREDJE" << endl;
            }else{
                cout << "NAPAKA: ZAPOREDJE NI UREJENO PADAJOCE" << endl;
            }

            cout << "Cas izvajanje => " << duration << "s" << endl;
            break;

        //KONEC
        case 6:
            cout << "Konec..." << endl;
            running = false;
        }
    }

    cin.ignore();
    cout << "Press any key to exit...";
    cin.get();
    return 0;
}
