#include<vector>
#include<iostream>
#include<string>
#include<list>
#include<fstream>
#include<sstream>
using namespace std;
class Dish;
class Menu;
class Stock;
class Ingredients {
	static int idCounter;
	int id;
	string name;
	int quantity;
	double price;
public:
	Ingredients(string name, double price) {
		this->id = ++idCounter;
		this->name = name;
		this->price = price;
	}
	Ingredients(string name, int quantity) {
		this->id = ++idCounter;
		this->name = name;
		this->quantity = quantity;
	}
	Ingredients(string name, int quantity, double price) {
		this->id = ++idCounter;
		this->name = name;
		this->quantity = quantity;
		this->price = price;
	}
	int get_Id()const {
		return id;
	}

	string getName()const {
		return name;
	}

	int getQuantity()const {
		return quantity;
	}

	int getPrice()const {
		return price;
	}
	void setQuantity(int quantity) {
		if (quantity >= 0)
		{
			this->quantity = quantity;
		}
		else {
			cout << "Miqdar menfi ola bilmez" << endl;
		}
	}
	void showIngredient()const {
		cout << "Ingredient id: " << get_Id() << endl;
		cout << "Ingredient name: " << getName() << endl;
		cout << "Ingredient count: " << getQuantity() << endl;
	};
	void ShowIngredient()const {
		cout << "Ingredient name: " << getName() << endl;
	};
	static Ingredients LoadFromFile(ifstream& file) {
		string name;
		int quantity;
		double price;

		getline(file, name, '#');
		file >> quantity;
		file.ignore();
		file >> price;
		file.ignore();

		return Ingredients(name, quantity, price);
	}

	static void WriteToFile(ofstream& file, const Ingredients& ingredient) {
		file << ingredient.getName() << "#"
			<< ingredient.getQuantity() << "#"
			<< ingredient.getPrice() << "\n";
	}

};


vector<Ingredients> inventory;

int Ingredients::idCounter = 0;
class Dish {
	static int static_id;
	int dish_id;
	string name;
	vector<Ingredients>ingredients;
	double price;
	int Dishcount;
public:
	static int oneDishCount;
	Dish(string name, double price) {
		static_id++;
		dish_id = static_id;
		this->name = name;
		this->price = price;
		this->Dishcount = 1;
	}
	Dish(string name, double price, int Dishcount) {
		static_id++;
		dish_id = static_id;
		this->name = name;
		this->price = price;
		this->Dishcount = Dishcount;
	}
	void WriteToFile(ofstream& file) const {
		file << name << "|" << price << "|" << getDishCount() << "\n";
	};
	Dish(string name, double price, int dishCount, vector<Ingredients> ingredients)
		: name(name), price(price), Dishcount(dishCount), ingredients(ingredients) {
		static_id++;
		dish_id = static_id;
	};
	vector<Ingredients> getIngredients() const {
		return ingredients;
	}

	string getName()const {
		return name;
	}
	double get_price()const {
		return price;
	}

	int getIngredientCount()const {
		return ingredients.size();
	}
	int getDishCount()const {
		return Dishcount;
	}
	void setDishCount(int Dishcount) {
		if (Dishcount >= 0)
		{
			this->Dishcount = Dishcount;
		}
	}
	void addIngredient(string ingredientName, int quantity) {

		ingredients.push_back(Ingredients(ingredientName, quantity));
	}
	int get_Id()const {
		return dish_id;
	}

	void Show_Ingredients()const {
		if (ingredients.empty())
		{
			cout << "Ingredient yoxdur!" << endl;
		}
		else {
			for (auto& ingredient : ingredients)
			{
				ingredient.ShowIngredient();
			}
		}
	}
	void showIngredients() const {
		cout << "Ingrediyentler: " << endl;
		if (ingredients.empty()) {
			cout << "Ingrediyent qeyd olunmayib!" << endl;
		}
		else {
			for (const auto& ingredient : ingredients) {
				ingredient.showIngredient();
			}
		}
	}
	int getDishId() const {
		return dish_id;
	}
	void increaseCount(int count) {
		count++;
	}

	void Show_Dish() const {
		cout << "--------------------------" << endl;
		cout << "Yemeyin id-si: " << dish_id << endl;
		cout << "Yemeyin adi: " << name << endl;
		cout << "Qiymeti: " << price << " AZN" << endl;
		cout << "--------------------------" << endl;
	}


};
int Dish::static_id = 0;
int Dish::oneDishCount = 0;
class User {
	static int static_id;
	int id;
	string username;
	string name;
	string password;
	double cash;
public:
	vector<Dish>basket;
	vector<Dish>& get_Basket() {
		return basket;
	}
	User() = default;
	User(string username, string name, string password) {
		static_id++;
		id = static_id;
		setUsername(username);
		setName(name);
		setPassword(password);
	}
	User(string username, string name, string password, double cash) {
		static_id++;
		id = static_id;
		setUsername(username);
		setName(name);
		setPassword(password);
		set_Cash(cash);
	}

	double get_Cash()const {
		return cash;
	}
	void set_Cash(double cash) {
		if (cash > 0)
		{
			this->cash = cash;
		}
	}

	User(string username, string name, string password, vector<Dish> basket)
		: username(username), name(name), password(password), basket(basket) {};
	string getUsername() const {
		return this->username;
	}
	string getName() const {
		return this->name;
	}
	string getPassword() const {
		return this->password;
	}
	int getId() const {
		return this->id;
	}



	void setUsername(string username) {
		while (username.length() <= 5) {
			cout << "Bu username cox qisadir.Zehmet olmasa en azi 5 xarakterli username daxil edin! ";
			cin >> username;
		}
		this->username = username;
	}
	void setName(string name) {
		while (name.length() <= 3) {
			cout << "Bu ad cox qisadir.Zehmet olmasa en azi 3 xarakterli ad daxil edin! ";
			cin >> name;
		}
		this->name = name;
	}
	void setPassword(string password) {
		while (password.length() <= 7) {
			cout << "Bu parol cox qisadir.Zehmet olmasa en azi 7 xarakterli parol daxil edin! ";
			cin >> password;
		}
		this->password = password;
	}


	void AddToBasket(vector<Dish>& basket, const Dish& newDish) {
		for (auto& dish : basket) {
			if (dish.get_Id() == newDish.get_Id()) {
				dish.setDishCount(dish.getDishCount() + newDish.getDishCount());
				return;
			}
		}
		basket.push_back(newDish);
	}

	void Show() const {
		cout << "ID: " << getId() << endl;
		cout << "Name: " << getName() << endl;
		cout << "Username: " << getUsername() << endl;
		cout << "Password: " << getPassword() << endl;
	}

	void show_Basket() const {
		cout << "------------------------- Sebetinizdeki Yemekler ----------------------" << endl;

		if (basket.empty()) {
			cout << "----------------------- Sebet bosdur -----------------------!" << endl;
			return;
		}

		for (const auto& dish : basket) {
			cout << "Yemeyin id-si: " << dish.getDishId() << endl;
			cout << "Yemeyin adi: " << dish.getName() << endl;
			cout << "Qiymeti: " << dish.get_price() << " AZN" << endl;
			cout << "Miqdari: " << dish.getDishCount() << endl;
			cout << "---------------------------------------------" << endl;
		}
	}

};
int User::static_id = 0;
class Account {
	list<User*> users;
	static int count;

public:
	bool CheckUser(string username) {
		for (auto user : users) {
			if (user->getUsername() == username) {
				return true;
			}
		}
		return false;
	}

	void SignUp() {
		string username;
		cout << "Username daxil edin(en az 5 xarakter): ";
		getline(cin, username);

		while (username.length() <= 5 || CheckUser(username)) {
			if (username.length() <= 5) {
				cout << "Bu username cox qisadir.En azi 5 xarakterli username daxil edin: ";
			}
			else {
				cout << "Bu username artiq istifade olunub.Zehmet olmasa basqa username daxil edin!" << endl;
			}
			getline(cin, username);
		}

		string name;
		cout << "Ad daxil edin(en az 3 xarakter olmalidir): ";
		getline(cin, name);
		while (name.length() <= 3) {
			cout << "Bu ad cox qisadir.En azi 3 xarakterli ad daxil edin: ";
			getline(cin, name);
		}

		string password;
		cout << "Parol daxil edin(en az 7 xarakterli olmalidir:) ";
		getline(cin, password);
		while (password.length() <= 7) {
			cout << "Bu password cox qisadir.Zehmet olmasa en az 7 xarakterli password daxil edin!" << endl;
			getline(cin, password);
		}

		User* new_user = new User(username, name, password);
		users.push_back(new_user);
		cout << "User ugurla qeydiyyatdan kecdi!" << endl;
		count++;
		ofstream outFile("users.txt", ios::app);
		if (!outFile) {
			cout << "Fayla yazilmadi!" << endl;
			return;
		}

		outFile << "Username: " << username << endl;
		outFile << "Name: " << name << endl;
		outFile << "Password: " << password << endl;
		outFile << "-------------------------------" << endl;
		outFile.close();
	}


	bool SignIn(string username, string name, string password) {
		for (auto user : users) {
			if (user->getUsername() == username && user->getName() == name) {
				if (user->getPassword() == password) {
					cout << "Hesabiniza ugurla daxil oldunuz!" << endl;
					return true;
				}
				else {
					cout << "Parol yalnisdir." << endl;
					return false;
				}
			}
		}
		cout << "Istifadeci tapilmadi!" << endl;
		return false;
	}


	void Show_All_Users() {
		for (auto user : users) {
			cout << "________________________________________" << endl;
			user->Show();
			cout << "________________________________________" << endl;
		}
	}
	void Show_All_Users() const {
		if (users.empty()) {
			cout << "Hal hazirda user yoxdur." << endl;
			return;
		}

		cout << "Userler: " << endl;
		for (auto user : users) {
			user->Show();
			cout << "------------------------" << endl;
		}
	}

	void load_Users_From_File() {
		ifstream inFile("users.txt");
		if (!inFile) {
			cout << "Fayl tapilmadi!" << endl;
			return;
		}

		string username, name, password;
		while (getline(inFile, username) && getline(inFile, name) && getline(inFile, password)) {
			username = username.substr(username.find(":") + 2);
			name = name.substr(name.find(":") + 2);
			password = password.substr(password.find(":") + 2);

			User* new_user = new User(username, name, password);
			users.push_back(new_user);
		}

		inFile.close();
	}
	void Delete_User(string username) {
		for (auto user : users) {
			if (user->getUsername() == username) {
				delete user;
				users.remove(user);
				count--;
				cout << "User silindi..." << endl;
				return;
			}
		}
		cout << "User tapilmadi..." << endl;
	}

	~Account() {
		for (auto user : users) {
			delete user;
		}
	}
};
int Account::count = 0;


class Restaurant {
	string name;
	double budget = 500;
	vector<Stock> stock;
public:
	Restaurant() = default;

	string get_Name() {
		return name;
	}
	double get_Budget()const {
		return budget;
	}
	Restaurant(string name, double budget) {
		this->name = name;
		this->budget = budget;
	}
	Restaurant(string name) {
		this->name = name;
	}
	void showRestaurantInfo() const {
		cout << "Restaurant Name: " << name << endl;
		cout << "Budget: " << budget << endl;
	}
	void set_Budget(double newBudget) {
		budget = newBudget;
	}
	void Add_Money(double amount) {
		budget += amount;
		cout << "Pul restoranin budcesine elave edildi!" << endl;
	}
	void Add_Money_For_Admin() {
		double amount;
		cout << "Elave etmek istediyiniz meblegi daxil edin: ";
		cin >> amount;
		budget += amount;
		cout << "Pul restoranin budcesine elave edildi!" << endl;
	}
	void Spend_Money(double amount) {
		if (budget > amount)
		{
			budget -= amount;
			cout << "Restoranin budcesinden pul cixildi" << endl;
		}
		else {
			cout << "Budcede kifayet qeder pul yoxdur" << endl;
		};
	};
	void LoadRestaurantInfoFromFile(const string& filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Fayl acilmadi!" << endl;
			return;
		}

		getline(file, name);
		file >> budget;

		file.close();
		cout << "Restaurant melumatlari fayldan oxundu: " << filename << endl;
	}

	void SaveRestaurantInfoToFile(const string& filename) const {
		ofstream file(filename);
		if (!file.is_open()) {
			cout << "Fayl acilmadi!" << endl;
			return;
		}

		file << name << endl;
		file << budget << endl;

		file.close();
		cout << "Restaurant melumatlari fayla yazildi: " << filename << endl;
	}

};
class Menu;
class Stock {
	vector<Ingredients> inventory;
public:
	vector<Ingredients>& getInventory() {
		return inventory;
	}
	void Add_Ingredient(Ingredients ingredient) {
		inventory.push_back(ingredient);
	}
	bool ReduceIngredientQuantity(string ingredientName, int reduceQuantity) {
		for (auto& ingredient : inventory) {
			if (ingredient.getName() == ingredientName) {
				if (ingredient.getQuantity() >= reduceQuantity) {
					ingredient.setQuantity(ingredient.getQuantity() - reduceQuantity);
					return true;
				}
				return false;
			}
		}
		return false;
	}

	void addIngredient(string ingredientName, int quantity) {
		for (auto& ingredient : inventory)
		{
			if (ingredient.getName() == ingredientName)
			{
				(ingredient.getQuantity() + quantity);
				cout << "Ingrediyent elave olundu." << endl;
				return;
			}
		}
		inventory.push_back(Ingredients(ingredientName, quantity, 0));
	}
	bool checkStock(const string& ingredientName, int requiredQuantity) {
		for (auto& ingredient : inventory) {
			if (ingredient.getName() == ingredientName && ingredient.getQuantity() >= requiredQuantity) {
				return true;
			}
		}
		return false;
	}
	void updateStock(const string& ingredientName, int usedQuantity) {
		for (auto& ingredient : inventory) {
			if (ingredient.getName() == ingredientName) {
				ingredient.setQuantity(ingredient.getQuantity() - usedQuantity);
				cout << ingredientName << " stokdan azaldildi.\n";
				return;
			}
		}
	}

	void Add_Ingredient(Restaurant& restaurant) {
		cout << "Elave etmek istediyiniz ingredientin adini daxil edin:";
		string ingredientName;
		int ingredientCount;
		getline(cin, ingredientName);
		bool check = false;
		for (auto& ing : getInventory())
		{
			if (ing.getName() == ingredientName)
			{
				check = true;
				cout << "Bu ingrediyentden stockda movcuddur! Elave etmek istediyiniz sayi daxil edin:";
				cin >> ingredientCount;
				cin.ignore();
				ing.setQuantity(ing.getQuantity() + ingredientCount);
				int totalPrice = ing.getPrice() * ingredientCount;
				if (restaurant.get_Budget() > totalPrice)
				{
					double totalRestaurantBudget = ((restaurant.get_Budget()) - totalPrice);
					restaurant.set_Budget(totalRestaurantBudget);
					cout << ingredientName << " stocka elave edildi" << endl;
					break;
				}
				else {
					cout << "Restoranin budcesinde kifayet qeder pul yoxdur!" << endl;
					return;
				}

			}
		}
		if (check == false)
		{
			cout << "Bu ingrediyentden stockda movcud deyil! Elave etmek istediyiniz sayi daxil edin:";
			cin >> ingredientCount;
			double ingQiymet;
			cout << "Bu ingrediyentin qiymetini daxil edin:";
			cin >> ingQiymet;
			cin.ignore();
			Ingredients new_ingredient(ingredientName, ingredientCount, ingQiymet);
			int totalPrice = ingredientCount * ingQiymet;
			if (restaurant.get_Budget() > totalPrice)
			{
				restaurant.set_Budget(restaurant.get_Budget() - totalPrice);
				inventory.push_back(new_ingredient);
				cout << "Inqrediyent stocka elave edildi!" << endl;
			}
			else {
				cout << "Restoranin budcesinde kifayet qeder pul yoxdur!" << endl;
				return;
			}
		}
	}

	void Add_Dish_With_Ingredients(vector<Ingredients>& inventory, string dishName, double price) {
		cout << "Yemek ucun lazim olan ingrediyent sayini daxil edin: ";
		int ingredientCount;
		cin >> ingredientCount;
		cin.ignore();
		while (ingredientCount > 0) {
			cout << "Ingredient adini daxil edin: ";
			string ingredientName;
			getline(cin, ingredientName);
			cout << "Yemek ucun bu ingrediyentden nece eded lazim oldugunu daxil edin: ";
			int ingredientQuantity;
			cin >> ingredientQuantity;
			cin.ignore();
			bool ingredientExists = false;
			for (auto& ingredient : inventory)
			{
				if (ingredient.getName() == ingredientName)
				{
					ingredientExists = true;
					if (ingredient.getQuantity() >= ingredientQuantity)
					{
						ingredient.setQuantity(ingredient.getQuantity() - ingredientQuantity);
						cout << ingredientName << " stokdan azaldildi.\n";
					}
					else {
						cout << "Stokda kifayet qeder " << ingredientName << " yoxdur.\n";
					}
					break;
				}
			}
			if (!ingredientExists) {
				cout << "Bu ingredient stokda movcud deyil.\n";
			}
			ingredientCount--;
		}
	}
	void Show_All_Stock()const {
		cout << "Stockda olan ingrediyentler:" << endl;
		cout << "---------------------------------------------------------------" << endl;
		for (auto& ingrediyent : inventory)
		{
			if (ingrediyent.getQuantity() > 0)
			{
				cout << "Ingrediyent id:" << ingrediyent.get_Id() << endl;
				cout << "Ingrediyent name: " << ingrediyent.getName() << endl;
				cout << "Ingrediyent sayi: " << ingrediyent.getQuantity() << endl;
				cout << "---------------------------------------------------------------" << endl;
			}
		}
	}
	void Show_All_Stock_For_Users()const {
		cout << "-------ingrediyentler---------" << endl;
		for (auto& ingrediyent : inventory)
		{
			if (ingrediyent.getQuantity() > 0)
			{
				cout << "Ingrediyent id:" << ingrediyent.get_Id() << endl;
				cout << "Ingrediyent name: " << ingrediyent.getName() << endl;
				cout << "---------------------------------------------------------------" << endl;
			}
		}
	}

	void Delete_Ingredient() {
		int deleteIngrediyentId;
		Show_All_Stock();
		cout << "Silmek istediyiniz ingrediyentin id-sini daxil edin: ";
		cin >> deleteIngrediyentId;
		cin.ignore();
		bool found = false;
		for (auto it = inventory.begin(); it != inventory.end(); ++it) {
			if (it->get_Id() == deleteIngrediyentId) {
				inventory.erase(it);
				found = true;
				cout << "Ingrediyent id: " << deleteIngrediyentId << " silindi." << endl;
				break;
			}
		}
		if (!found) {
			cout << "Ingrediyent id: " << deleteIngrediyentId << " tapilmadi." << endl;
		}
	}
	void saveStockToFile(const string& filename) {
		ofstream outFile(filename);
		if (!outFile) {
			cout << "Fayl acilmadi!" << endl;
			return;
		}

		outFile << inventory.size() << endl;
		for (const auto& ingredient : inventory) {
			outFile << ingredient.getName() << endl;
			outFile << ingredient.getQuantity() << endl;
			outFile << ingredient.getPrice() << endl;
		}

		outFile.close();
		cout << "Stok fayla yazildi." << endl;
	}

	void loadStockFromFile(const string& filename) {
		ifstream inFile(filename);
		if (!inFile) {
			cout << "Fayl oxumaq ucun acila bilmedi!" << endl;
			return;
		}

		int inventorySize;
		inFile >> inventorySize;
		inFile.ignore();

		for (int i = 0; i < inventorySize; ++i) {
			string name;
			int quantity;
			double price;

			getline(inFile, name);
			inFile >> quantity;
			inFile >> price;
			inFile.ignore();

			Ingredients ingredient(name, quantity, price);
			inventory.push_back(ingredient);
		}

		inFile.close();
		cout << "Stok fayldan oxundu." << endl;
	}

};

class Ingredients;


class Menu {
	vector<Dish>dishes;
public:
	vector<Dish>& get_Dishes() {
		return dishes;
	}
	void Add_Dish(Dish& dish) {
		dishes.push_back(dish);
	}
	void removeDish(int dishId) {
		auto it = std::find_if(dishes.begin(), dishes.end(), [dishId](const Dish& dish) {
			return dish.get_Id() == dishId;
			});

		if (it != dishes.end()) {
			dishes.erase(it);
			cout << "Yemek silindi!" << endl;
		}
		else {
			cout << "Bu id-li yemek tapilmadi!" << endl;
		}
	}


	void Show_Menu_For_Users()const {
		if (dishes.empty())
		{
			cout << "Menyuda hecne yoxdur!" << endl;
			return;
		}
		else {
			cout << "\n\n\n\nMenyu: " << endl;
			cout << "___________________________" << endl;
			for (auto& dish : dishes)
			{
				dish.Show_Dish();
				cout << "___________________________" << endl;
			}
		}
	};


	void Add_Ingredients_To_Dish(Restaurant restaurant, string dishName, string ingredientName, int quantity, double ingredientCost) {
		if (ingredientCost * quantity > restaurant.get_Budget())
		{
			cout << "Budcede bu qeder pul yoxdur!" << endl;
			return;
		}
		for (auto& dish : dishes)
		{
			if (dish.getName() == dishName)
			{
				dish.addIngredient(ingredientName, quantity);
				(restaurant.Spend_Money(ingredientCost * quantity));
				cout << "Ingredient elave edildi." << ingredientName << "->" << dishName << endl;
				cout << "Qalan budce:" << restaurant.get_Budget() << "Azn" << endl;
				if (dish.getIngredientCount() >= 5) {
					cout << "Yemek elave edile biler!" << endl;
				}
				return;
			}
		}
		cout << "Yemek tapilmadi" << endl;
	}

	void Add_With_Check_Dishes(Stock& stock, Menu& menu, Restaurant& restaurant) {
		string newDishName;
		cout << "Yemeyin adini daxil edin: ";
		getline(cin, newDishName);

		bool dishFound = false;
		for (auto& dish : dishes) {
			if (dish.getName() == newDishName) {
				dishFound = true;
				dish.setDishCount(dish.getDishCount() + 1);
				cout << "Bu yemek menyuda movcuddur! Sayi artirildi!" << endl;
				return;
			}
		}

		if (!dishFound) {
			int ingredientCount;
			cout << "Bu yemek ucun lazim olan ingrediyentlerin sayini daxil edin: ";
			cin >> ingredientCount;
			cin.ignore();

			vector<Ingredients> requiredIngredients;

			while (ingredientCount > 0) {
				string ingredientName;
				cout << "Ingrediyentin adini daxil edin: ";
				getline(cin, ingredientName);

				bool ingredientFound = false;

				for (auto& ingredient : stock.getInventory()) {
					if (ingredient.getName() == ingredientName) {
						ingredientFound = true;
						int neededQuantity;
						cout << "Bu ingrediyentden nece eded lazim oldugunu yazin: ";
						cin >> neededQuantity;
						cin.ignore();

						if (ingredient.getQuantity() >= neededQuantity) {
							ingredient.setQuantity(ingredient.getQuantity() - neededQuantity);
							cout << ingredient.getName() << " stockdan azaldildi!" << endl;
							requiredIngredients.push_back(Ingredients(ingredientName, neededQuantity));
						}
						else {
							cout << "Bu ingrediyentden stockda kifayet qeder yoxdur." << endl;
							return;
						}
						break;
					}
				}

				if (!ingredientFound) {
					cout << "Bu ingrediyent stockda yoxdur." << endl;
					double newIngPrice;
					int newIngredientQuantity;
					cout << "Ingrediyentden nece eded lazim oldugunu daxil edin: ";
					cin >> newIngredientQuantity;
					cout << "Bu ingrediyentin qiymetini daxil edin:";
					cin >> newIngPrice;
					cin.ignore();
					Ingredients newIngrediyent(ingredientName, newIngredientQuantity, newIngPrice);
					int totalIngPrice = newIngPrice * newIngredientQuantity;
					if (restaurant.get_Budget() > totalIngPrice)
					{
						stock.Add_Ingredient(newIngrediyent);
						requiredIngredients.push_back(Ingredients(ingredientName, newIngredientQuantity));
						cout << "Stocka bu ingrediyent daxil edildi!" << endl;
						restaurant.set_Budget(restaurant.get_Budget() - totalIngPrice);
					}
					else {
						cout << "Restoranin budcesinde kifayet qeder pul yoxdur!";
						return;
					}

				}
				ingredientCount--;
			}

			double newDishPrice;
			cout << "Yemeyin qiymetini daxil edin: ";
			cin >> newDishPrice;
			cin.ignore();

			Dish newDish(newDishName, newDishPrice, 1, requiredIngredients);
			menu.Add_Dish(newDish);

			cout << "Stocka yeni yemek elave edildi: " << newDishName << endl;
		}
	}
	void Delete_Dish() {
		int deleteDishId;
		Show_Menu();
		cout << "Silmek istediyiniz yemeyin id-sini daxil edin: ";
		cin >> deleteDishId;
		cin.ignore();

		bool found = false;

		for (auto it = dishes.begin(); it != dishes.end(); ++it) {
			if (it->get_Id() == deleteDishId) {
				dishes.erase(it);
				found = true;
				cout << "Yemek ID: " << deleteDishId << " silindi." << endl;
				break;
			}
		}
		if (!found) {
			cout << "Yemek id: " << deleteDishId << " tapilmadi." << endl;
		}
	}

	void Dish_About() {
		int count = 0;
		for (auto& dish : dishes) {
			cout << "~~~~~~~~~~~~~Yemek " << count << "~~~~~~~~~~~~~~~~~~~~~" << endl;
			count++;
			cout << "Dish name: " << dish.getName() << endl;
			cout << "Dish price: " << dish.get_price() << endl;
			cout << "-----Yemeyin ingrediyentleri-----" << endl;
			dish.Show_Ingredients();
			cout << "---------------------------" << endl;
		}
	}

	void Order_For_User(User& user, Dish& dish, Restaurant& restaurant, Stock& stock) {
		Show_Menu_For_Users();

		int orderId;
		cout << "Sifaris etmek istediyiniz yemeyin id-sini daxil edin: ";
		cin >> orderId;
		cin.ignore();

		bool check = false;

		cout << "Yemeye elave ingrediyentler isteyersiniz?" << endl;
		cout << "1-Beli 2-Xeyr" << endl;
		cout << "Seciminizi daxil edin: ";
		int choice;
		cin >> choice;
		cin.ignore();

		if (choice == 1) {
			int choiceSay;
			cout << "Nece eded ferqli inqrediyent elave edeceksiniz? Sayi daxil edin: ";
			cin >> choiceSay;
			cin.ignore();
			stock.Show_All_Stock_For_Users();

			while (choiceSay > 0) {
				cout << "Elave etmek istediyiniz inqrediyentin id-sini daxil edin: ";
				int ingredientId;
				cin >> ingredientId;
				cin.ignore();

				bool ingredientFound = false;
				for (auto& ing : stock.getInventory()) {
					if (ing.get_Id() == ingredientId) {
						ingredientFound = true;

						cout << "Elave etmek istediyiniz sayi (kq, ml, l, say) daxil edin: ";
						int ingMiqdar;
						cin >> ingMiqdar;
						cin.ignore();

						if (ing.getQuantity() >= ingMiqdar) {
							ing.setQuantity(ing.getQuantity() - ingMiqdar);
							cout << ing.getName() << " elave edildi." << endl;
						}
						else
						{
							cout << "Stockda bu inqrediyentden kifayet qeder yoxdur!" << endl;
						}
						break;
					}
				}

				if (!ingredientFound) {
					cout << "Stockda bu inqrediyentden yoxdur!" << endl;
				}

				choiceSay--;
			}
		}
		else if (choice == 2) {
			cout << "Buyurun davam edin." << endl;
		}
		else {
			cout << "Bele bir secim yoxdur!" << endl;
			return;
		}

		for (auto& basketDish : user.basket) {
			if (basketDish.get_Id() == orderId) {
				basketDish.setDishCount(basketDish.getDishCount() + 1);
				restaurant.set_Budget(restaurant.get_Budget() + basketDish.get_price());
				cout << "Yemek sayi artirildi!" << endl;
				check = true;
				break;
			}
		}

		if (!check) {
			for (auto& menuDish : dishes) {
				if (menuDish.get_Id() == orderId) {
					menuDish.setDishCount(1);
					user.AddToBasket(user.basket, menuDish);
					restaurant.set_Budget(restaurant.get_Budget() + menuDish.get_price());
					cout << "Yemek baskete elave edildi!" << endl;
					check = true;
					break;
				}
			}
		}

		if (!check) {
			cout << "Bele bir id-li yemek tapilmadi!" << endl;
		}
	}
	void removeFromBasket(User& user, Restaurant& restaurant, Dish& dish) {
		user.show_Basket();
		int dishId;
		cout << "Silmek istediyiniz yemeyin id-sini daxil edin:";
		cin >> dishId;
		cin.ignore();
		for (auto it = user.basket.begin(); it != user.basket.end(); ++it) {
			if (it->get_Id() == dishId) {
				user.basket.erase(it);
				cout << "Yemek silindi: ID " << dishId << endl;
				restaurant.set_Budget(restaurant.get_Budget() - dish.get_price());
				return;
			}
		}
		cout << "Bu ID-li yemek tapilmadi: " << dishId << endl;
	}
	void SaveMenuToFile(const string& filename) const {
		ofstream file(filename, ios::out);
		if (!file.is_open()) {
			cout << "Fayl acilmadi!" << endl;
			return;
		}

		for (const auto& dish : dishes) {
			dish.WriteToFile(file);
		}

		file.close();
		cout << "Menyu fayla yazildi: " << filename << endl;
	}

	void LoadMenuFromFile(const string& filename) {
		ifstream file(filename, ios::in);
		if (!file.is_open()) {
			cout << "Fayl acilmadi!" << endl;
			return;
		}

		dishes.clear();
		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string name;
			string priceStr, countStr;
			getline(ss, name, '|');
			getline(ss, priceStr, '|');
			getline(ss, countStr);

			double price = stod(priceStr);
			int count = stoi(countStr);

			dishes.push_back(Dish(name, price, count));
		}

		file.close();
		cout << "Menyu fayldan oxundu: " << filename << endl;
	}

	void Show_Menu() const {
		if (dishes.empty()) {
			cout << "Menyuda hecne yoxdur!" << endl;
			return;
		}
		cout << "\n\n\n\nMenyu: " << endl;
		cout << "___________________________" << endl;
		for (const auto& dish : dishes) {
			dish.Show_Dish();
			cout << "___________________________" << endl;
		}
	}
	void saveDishesToFile(const string& filename) {
		ofstream outFile(filename);
		if (!outFile) {
			cout << "Fayl yazmaq ucun acilmadi!" << endl;
			return;
		}

		outFile << dishes.size() << endl;
		for (const auto& dish : dishes) {
			outFile << dish.getName() << endl;
			outFile << dish.get_price() << endl;

			outFile << dish.getIngredients().size() << endl;
			for (const auto& ingredient : dish.getIngredients()) {
				outFile << ingredient.getName() << endl;
			}
		}

		outFile.close();
		cout << "Yemekler fayla yazildi." << endl;
	}

};
void admiN(Stock stock, Dish dish, Menu& menu, Restaurant restaurant, vector<Ingredients>& ingredients) {
	string admin_Name = "nurana2002";
	string admin_Password = "nurana123";
	string adminName, adminPassword;

	cout << "Enter admin name: ";
	getline(cin, adminName);
	cout << "Enter admin password: ";
	getline(cin, adminPassword);

	while (adminName != admin_Name || adminPassword != admin_Password) {
		cout << "Admin adi ve ya sifresi yanlisdir. Yeniden yazin." << endl;
		cout << "Enter admin name: ";
		getline(cin, adminName);
		cout << "Enter admin password: ";
		getline(cin, adminPassword);
	}
	cout << "Admin kimi giris etdiniz!" << endl;

	while (true) {
		cout << "\nAdmin Paneli:" << endl;
		cout << "1. Menyuya bax" << endl;
		cout << "2. Menyuya yemek elave et" << endl;
		cout << "3. Inqrediyent elave et" << endl;
		cout << "4. Ingrediyenti sil" << endl;
		cout << "5. Restoran melumatlari" << endl;
		cout << "6. Menyudan yemek sil" << endl;
		cout << "7. Stocka bax" << endl;
		cout << "8. Restoranin budcesine pul elave et" << endl;
		cout << "9.Yemeklere inqrediyentlerle birlikde bax" << endl;
		cout << "10. Cixis" << endl;
		cout << "Seciminizi daxil edin: ";

		int choice;
		cin >> choice;
		cin.ignore();

		if (choice == 1) {
			menu.SaveMenuToFile("menu.txt");
			menu.LoadMenuFromFile("menu.txt");
			menu.Show_Menu();
		}
		else if (choice == 2) {
			menu.Add_With_Check_Dishes(stock, menu, restaurant);
		}
		else if (choice == 3) {
			stock.saveStockToFile("stock_data.txt");
			stock.loadStockFromFile("stock_data.txt");
			stock.Add_Ingredient(restaurant);
		}
		else if (choice == 4) {
			stock.Delete_Ingredient();
		}
		else if (choice == 5) {
			restaurant.SaveRestaurantInfoToFile("restaurant_info.txt");
			restaurant.LoadRestaurantInfoFromFile("restaurant_info.txt");
			restaurant.showRestaurantInfo();
		}
		else if (choice == 6) {
			menu.Delete_Dish();
		}
		else if (choice == 7) {
			stock.Show_All_Stock();
		}
		else if (choice == 8) {
			restaurant.Add_Money_For_Admin();
		}
		else if (choice == 9) {
			menu.Dish_About();
		}
		else if (choice == 10) {
			cout << "Admin panelinden cixis edildi." << endl;
			break;
		}
		else {
			cout << "Duzgun secim edin." << endl;
		}
	}
}
void User_Operation(Menu& menu, Dish& dish, User& user, Restaurant& restaurant, Stock& stock) {
	cout << "Welcome" << endl;
	while (true) {
		cout << "--------Secimler-----------" << endl;
		cout << "----------1.Menyuya bax----------" << endl;
		cout << "------------2.Yemekler haqqinda melumat---------" << endl;
		cout << "------------3.Yemek sifarisi et---------" << endl;
		cout << "------------4.Baskete bax---------" << endl;
		cout << "--------------5.Basketden yemeyi sil----------" << endl;
		cout << "-------------6.Cixis--------------" << endl;

		int choice;
		cout << "Seciminizi daxil edin:";
		cin >> choice;
		cin.ignore();

		if (choice == 1) {
			menu.Show_Menu();
		}
		else if (choice == 2) {
			menu.Dish_About();
		}
		else if (choice == 3) {
			menu.Order_For_User(user, dish, restaurant, stock);
		}
		else if (choice == 4) {
			user.show_Basket();
		}
		else if (choice == 5) {
			menu.removeFromBasket(user, restaurant, dish);
		}
		else if (choice == 6) {
			cout << "User panelden cixis edildi" << endl;
			break;
		}
	}
}
void Start(Account& account, Menu& menu, Restaurant& restaurant, vector<Ingredients>& ingredients, Stock& stock, Dish& dish, User& user) {
	cout << "-------Welcome---------!!!" << endl;
	cout << "1. Admin Panel  2. User Panel" << endl;
	cout << "Enter choice: ";
	int choice;
	cin >> choice;
	cin.ignore();

	if (choice == 1) {
		admiN(stock, dish, menu, restaurant, ingredients);
	}
	else if (choice == 2) {
		cout << "1. Sign Up(Qeydiyyat)  2. Sign In (Daxil olun)" << endl;
		cout << "Enter choice: ";
		int user_choice;
		cin >> user_choice;
		cin.ignore();
		if (user_choice == 1) {
			account.SignUp();
			User_Operation(menu, dish, user, restaurant, stock);
		}
		else if (user_choice == 2) {
			string username, name, password;
			cout << "Enter username: ";
			getline(cin, username);
			cout << "Enter name: ";
			getline(cin, name);
			cout << "Enter password: ";
			getline(cin, password);

			if (account.SignIn(username, name, password)) {
				User_Operation(menu, dish, user, restaurant, stock);
			}
			else {
				cout << "Daxil ola bilmediniz.Bir daha yoxlayin.\n";
			}
		}
		else {
			cout << "Wrong choice.." << endl;
		}
	}
	else {
		cout << "Wrong choice..." << endl;
	}
};

void main() {
	Restaurant Restoran("Kepez");
	Stock stock;
	Menu menu;
	Account account;
	User user;

	Ingredients ingredient1("pamidor", 20);
	Ingredients ingredient2("yag", 320);
	Ingredients ingredient3("pendir", 230);
	Ingredients ingredient4("yumurta", 50);
	Ingredients ingredient5("kartof", 200);
	Ingredients ingredient6("kahi", 210);
	Ingredients ingredient7("alma", 520);
	Ingredients ingredient8("xiyar", 100);
	Ingredients ingredient9("duz", 920);
	Ingredients ingredient10("istiot", 120);
	Ingredients ingredient11("biber", 120);
	Ingredients ingredient12("corek", 950);

	vector<Ingredients>Inqrediyentler;

	Inqrediyentler.push_back(ingredient1);
	Inqrediyentler.push_back(ingredient2);
	Inqrediyentler.push_back(ingredient3);
	Inqrediyentler.push_back(ingredient4);
	Inqrediyentler.push_back(ingredient5);
	Inqrediyentler.push_back(ingredient6);
	Inqrediyentler.push_back(ingredient7);
	Inqrediyentler.push_back(ingredient8);
	Inqrediyentler.push_back(ingredient9);
	Inqrediyentler.push_back(ingredient10);
	Inqrediyentler.push_back(ingredient11);
	Inqrediyentler.push_back(ingredient12);

	vector<Ingredients>Inqrediyentlerr;
	Inqrediyentlerr.push_back(ingredient1);
	Inqrediyentlerr.push_back(ingredient2);
	Inqrediyentlerr.push_back(ingredient3);
	Inqrediyentlerr.push_back(ingredient4);

	vector<Ingredients>Inqrediyentlerr1;
	Inqrediyentlerr.push_back(ingredient4);
	Inqrediyentlerr.push_back(ingredient5);
	Inqrediyentlerr.push_back(ingredient6);


	vector<Ingredients>Inqrediyentler2;
	for (auto& ing : Inqrediyentler)
	{
		Inqrediyentler2.push_back(ing);
	}
	//---------------------------------------------
	vector<Ingredients>Ingrediyentler3;

	for (auto& ing : Inqrediyentlerr)
	{
		Ingrediyentler3.push_back(ing);
	}
	//------------------------------------------
	vector<Ingredients>Ingrediyentler4;

	for (auto& ing : Inqrediyentlerr1)
	{
		Ingrediyentler4.push_back(ing);
	}
	//-----------------------------------------
	for (auto& ingredient : Inqrediyentler)
	{
		stock.Add_Ingredient(ingredient);
	}

	Dish dish1("Pizza", 15.99, 20, Inqrediyentler2);
	Dish dish2("Salad", 45.99, 50, Ingrediyentler3);
	Dish dish3("Burger", 15.99, 150, Ingrediyentler3);
	Dish dish4("Soup", 5.99, 50, Inqrediyentler2);
	Dish dish5("Pasta", 35.99, 20, Ingrediyentler3);
	Dish dish6("Pide", 32, 20, Inqrediyentler2);

	Menu menu1;
	vector<Dish>dishes;
	dishes.push_back(dish1);
	dishes.push_back(dish2);
	dishes.push_back(dish3);
	dishes.push_back(dish4);
	dishes.push_back(dish5);
	dishes.push_back(dish6);
	for (auto& dish : dishes)
	{
		menu1.Add_Dish(dish);
	}

	while (true) {
		Start(account, menu1, Restoran, Inqrediyentler, stock, dish1, user);
	};
};;