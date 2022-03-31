#include<iostream>
#include<string.h>
using namespace std;

class CRC {
    string input,divisor,dividend,result;
    string data_rec;
    int len_dividend, len_gen;

public:
    string extraXor(string a, string b)
    {
        string result="";
        if(a[0]=='0')
            return a.substr(1);
        else
        {
            for(int i=0;i<len_gen;i++)
            {
                result=result+(a[i]==b[i]?'0':'1');
            }

            return result.substr(1);
        }
    }
    void  moduloDiv()
    {
        string tempDiv=divisor;
        string tempDividend=dividend.substr(0, len_gen);
        int j=len_gen;
        while(j < len_dividend)
        {
            tempDividend= extraXor(tempDividend, tempDiv);
            tempDividend= tempDividend + dividend[j];
            j++;
        }
        result= input + extraXor(tempDividend, tempDiv);
    }
    void getdata()
    {
        cout<<"\nEnter Input: ";
        cin>>input;
        cout<<"\nEnter coefficients of generator polynomial: ";
        cin>>divisor;

        len_gen=divisor.length();
        dividend=input;
        int r=len_gen-1;
        for(int i=0;i<r;i++)
        {
            dividend= dividend + '0';
        }
        len_dividend=dividend.length();
        moduloDiv();
    }
    void sender_side()
    {
        cout<<"Input: "<<input<<"\n";
        cout<<"Polynomial: "<<divisor<<"\n";
        cout << "Dividend: " << dividend << "\n";
        cout<<"Data to send: "<<result<<"\n";

    }
    void receiver_side()
    {
        cout<<"\nEnter Data Received: ";
        cin>>data_rec;

        string temp_div=divisor;
        string temp_divident=data_rec.substr(0,len_gen);
        int j=len_gen;
        while(j<data_rec.length())
        {
            temp_divident= extraXor(temp_divident, temp_div);
            temp_divident=temp_divident+data_rec[j];
            j++;
        }
        string error= extraXor(temp_divident, temp_div);
        cout<<"reminder is: "<<error;

        bool flag=0;
        for(int i=0;i<len_gen-1;i++)
        {
            if(error[i]=='1')
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\nCorrect Data Received Without Any Error";
        else
            cout<<"\nData Received Contain Some  Error";
    }
};

int main() {
    CRC crc;
    crc.getdata();
    crc.sender_side();
    crc.receiver_side();
    return 0;
}