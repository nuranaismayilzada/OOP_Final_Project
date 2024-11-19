#include<iostream>
#include<string>
#include<list>
#include<vector>
using namespace std;

class User {
	static int static_id;
	int id;
	string username;
	string name;
	string password;

public:
	User(string username, string name, string password) {
		static_id++;
		id = static_id;
		setUsername(username);
		setName(name);
		setPassword(password);
	}

	// get methods
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
			cout << "The username is too short. Please enter a username with more than 5 characters: ";
			cin >> username;
		}
		this->username = username;
	}
	void setName(string name) {
		while (name.length() <= 3) {
			cout << "The name is too short. Please enter a name with more than 3 characters: ";
			cin >> name;
		}
		this->name = name;
	}
	void setPassword(string password) {
		while (password.length() <= 7) {
			cout << "Password length is too short. Please enter a password with more than 7 characters: ";
			cin >> password;
		}
		this->password = password;
	}

	// Show method
	void Show() const {
		cout << "ID: " << getId() << endl;
		cout << "Name: " << getName() << endl;
		cout << "Username: " << getUsername() << endl;
		cout << "Password: " << getPassword() << endl;
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
		cout << "Enter username (more than 5 characters): ";
		getline(cin, username);

		while (username.length() <= 5 || CheckUser(username)) {
			if (username.length() <= 5) {
				cout << "The username is too short. Please enter a username with more than 5 characters: ";
			}
			else {
				cout << "This username is already in use. Please enter a different username." << endl;
			}
			getline(cin, username);
		}

		string name;
		cout << "Enter name (more than 3 characters): ";
		getline(cin, name);
		while (name.length() <= 3) {
			cout << "The name is too short. Please enter a name with more than 3 characters: ";
			getline(cin, name);
		}

		string password;
		cout << "Enter password (more than 7 characters): ";
		getline(cin, password);
		while (password.length() <= 7) {
			cout << "Password length is too short. Please enter a password with more than 7 characters: ";
			getline(cin, password);
		}

		User* new_user = new User(username, name, password);
		users.push_back(new_user);
		cout << "User registered successfully!" << endl;
		count++;
	}

	void SignIn(string username, string name, string password) {
		bool userFound = false;
		for (auto user : users) {
			if (user->getUsername() == username && user->getName() == name) {
				userFound = true;
				if (user->getPassword() == password) {
					cout << "You have successfully logged in!" << endl;
					return;
				}
				else {
					cout << "Password is incorrect." << endl;
					return;
				}
			}
		}

		if (!userFound) {
			cout << "User not found!" << endl;
		}
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
	void Delete_User(string username) {
		for (auto user : users) {
			if (user->getUsername() == username) {
				delete user;
				users.remove(user);
				count--;
				cout << "User deleted..." << endl;
				return;
			}
		}
		cout << "User not found..." << endl;
	}

	~Account() {
		for (auto user : users) {
			delete user;
		}
	}
};

int Account::count = 0;



class Ingredients {

	static int idCounter;
	int id;
	string name;
	int quantity;
public:
	Ingredients(string name, int quantity) {
		this->id = ++idCounter;
		this->name = name;
		this->quantity = quantity;
	}

	int getId()const {
		return id;
	}

	string getName()const {
		return name;
	}

	int getQuantity()const {
		return quantity;
	}

	void showIngredient()const {
		cout << "Ingredient id: " << id << endl;
		cout << "Ingredient name: " << name << endl;
		cout << "Ingredient count: " << quantity << endl;
	};
};
int Ingredients::idCounter = 0;

class Dish {
	string name;
	vector<Ingredients>ingredients;
	double price;
public:
	Dish(string name,double price) {
		this->name = name;
		this->price = price;
	}
	string getName()const {
		return name;
	}
	double get_price()const {
		return price;
	}
	//Yemek ucun inqrediyent elave etmek
	void addIngredient(string ingredientName, int quantity) {
		ingredients.push_back(Ingredients(ingredientName, quantity));
	}

	void Show_Ingredients()const {
		cout << "Ingredientler:" << endl;
		if (ingredients.empty())
		{
			cout << "Ingredient yoxdur!" << endl;
		}
		else {
			for (auto& ingredient : ingredients)
			{
				ingredient.showIngredient();
			}
		}
	}

	void Show_Dish()const {
		cout << "Yemeyin adi: " << getName() << endl;
		cout << "Yemeyin qiymeti: " << get_price()<<endl;
		Show_Ingredients();
	}
};

class Menu {
	vector<Dish>dishes;
	double budget;
public:
	Menu() = default;
	Menu(double budget) {
		this->budget = budget;
	}
	void Add_Dish(string dishName,double price) {
		dishes.push_back(Dish(dishName,price));
		cout << "Yemek elave edildi: " << dishName << "(" << price << "Azn)" << endl;
	}
	void Add_Ingredients_To_Dish(string dishName, string ingredientName, int quantity, double ingredientCost) {
		if (ingredientCost*quantity>budget)
		{
			cout << "Budcede bu qeder pul yoxdur!" << endl;
				return;
		}
		for (auto& dish : dishes)
		{
			if (dish.getName() == dishName)
			{
				dish.addIngredient(ingredientName, quantity);
				budget -= ingredientCost * quantity;
				cout << "Ingredient elave edildi." << ingredientName << "->" << dishName << endl;
				cout << "Qalan budce:" << budget << "Azn" << endl;
				return;
			}
		}
		cout << "Yemek tapilmadi" << endl;
	}
	void Show_Menu()const {
		if (dishes.empty())
		{
			cout << "Menyuda hecne yoxdur!" << endl;
		}
		else {
			cout << "Menyu: " << endl;
			for (auto &dish : dishes)
			{
				dish.Show_Dish();
				cout << "________________________________" << endl;
			}
		}
	}
};
void admiN(Menu menu) {
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
		cout << "4.Ingrediyenti sil" << endl;
		cout << "5. Cixis" << endl;
		cout << "Seciminizi daxil edin: ";

		int choice;
		cin >> choice;
		cin.ignore();

		if (choice == 1) {
			menu.Show_Menu();
		}
		else if (choice == 2) {
			string dishName;
			double price;
			cout << "Elave etmek istediyiniz yemeyin adini daxil edin: ";
			getline(cin, dishName);
			cout << "Elave etmek istediyiniz yemeyin qiymetini daxil edin: ";
			cin >> price;
			cin.ignore();
			menu.Add_Dish(dishName,price);
		}
		else if (choice == 3) {
			string dishName, ingredientName;
			int quantity;
			double cost;
			cout << "Yemeyin adini daxil edin: ";
			getline(cin, dishName);
			cout << "Ingredientin adini daxil edin: ";
			getline(cin, ingredientName);
			cout << "Ingredientin miqdarini: ";
			cin >> quantity;
			cout << "Bir ededinin qiymetini daxil edin: ";
			cin >> cost;
			cin.ignore();
			menu.Add_Ingredients_To_Dish(dishName, ingredientName, quantity, cost);
		}
		else if (choice == 4) {
			cout << "gozleyir" << endl;
		}
		else if (choice == 5) {
			cout << "Admin panelinden cixis edildi." << endl;
			break;
		}
		else {
			cout << "Duzgun secim edin." << endl;
		}
	}
}

void Start(Account& account, Menu& menu) {
	cout << "Welcome!!!" << endl;
	cout << "1. Admin Panel  2. User Panel" << endl;
	cout << "Enter choice: ";
	int choice;
	cin >> choice;
	cin.ignore();

	if (choice == 1) {
		admiN(menu);
	}
	else if (choice == 2) {
		cout << "1. Sign Up(Qeydiyyat)  2. Sign In (Daxil olun)" << endl;
		cout << "Enter choice: ";
		int user_choice;
		cin >> user_choice;
		cin.ignore();
		if (user_choice == 1) {
			account.SignUp();
		}
		else if (user_choice == 2) {
			string username, name, password;
			cout << "Enter username: ";
			getline(cin, username);
			cout << "Enter name: ";
			getline(cin, name);
			cout << "Enter password: ";
			getline(cin, password);
			account.SignIn(username, name, password);
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
	Menu menu;
	Account account;
	while (true) {
		Start(account,menu);
	}
}
