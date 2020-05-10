#include <iostream>
#include <string>
#include <cassert>


class BankAccount
{
    private:
        // TODO: declare member variables
        int accountNumber_;
        std::string ownerName_;
        int availableBalance_;

    public:
        //Constructor with private member initialization
        BankAccount():accountNumber_(0),ownerName_("abc"),availableBalance_(0){};

        // TODO: declare setters
        void setAccountNumber(const int an);
        void setOwnerName(const std::string on);
        void setAvailableFunds(const int af);

        // TODO: declare getters
        int getAccountNumber() const {return accountNumber_;};
        std::string getOwnerName() const {return ownerName_;};
        int getAvalilableFunds() const {return availableBalance_;};
};


// TODO: implement setters
void BankAccount::setAccountNumber(const int an){
    accountNumber_ = an;
}

void BankAccount::setOwnerName(const std::string on){
    ownerName_ = on;
}

void BankAccount::setAvailableFunds(const int af){
    availableBalance_ = af;
}


int main(){
    // TODO: instantiate and output a bank account
    BankAccount ba_obj;

    ba_obj.setOwnerName("Puneet");
    ba_obj.setAccountNumber(000000);
    ba_obj.setAvailableFunds(10000);

    assert(ba_obj.getOwnerName() == "Puneet");
    assert(ba_obj.getAccountNumber() == 000000);
    assert(ba_obj.getAvalilableFunds() == 10000);

}