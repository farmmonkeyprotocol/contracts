#include <eosio/eosio.hpp>
using namespace eosio;

CONTRACT farmmonkey : public contract {
   public:
      using contract::contract;

      farmmonkey(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

      ACTION hi( name nm );

      using hi_action = action_wrapper<"hi"_n, &farmmonkey::hi>;
      
      ACTION upsert(name user, std::string first_name, std::string last_name, std::string street, std::string city, std::string state);

      using upsert_action = action_wrapper<"upsert"_n, &farmmonkey::upsert>;
      
      ACTION erase(name user);

      using erase_action = action_wrapper<"erase"_n, &farmmonkey::erase>;
      

   private:
      struct [[eosio::table]] person {
         name key;
         std::string first_name;
         std::string last_name;
         std::string street;
         std::string city;
         std::string state;

         uint64_t primary_key() const { return key.value;}
      };

      typedef eosio::multi_index<"people"_n, person> address_index;
};

EOSIO_DISPATCH(farmmonkey, (hi)(upsert)(erase))