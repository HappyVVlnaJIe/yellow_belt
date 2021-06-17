#include <iostream>
#include <string>

void SendSms(const std::string& number, const std::string& message) {
	std::cout << "Send '" << message << "' to number " << number << std::endl;
}

void SendEmail(const std::string& email, const std::string& message) {
	std::cout << "Send '" << message << "' to e-mail " << email << std::endl;
}

class INotifier {
public:
	virtual void Notify(const std::string& message) const=0;
};

class SmsNotifier : public INotifier {
public:
	SmsNotifier(const std::string& phone_number) : _phone_number(phone_number) {}
	void Notify(const std::string& message) const override;
private:
	const std::string _phone_number;
};

class EmailNotifier : public INotifier {
public:
	EmailNotifier(const std::string& email) : _email(email) {}
	void Notify(const std::string& message) const override;
private:
	const std::string _email;
};

void SmsNotifier::Notify(const std::string& message) const {
	SendSms(this->_phone_number, message);
}

void EmailNotifier::Notify(const std::string& message) const {
	SendEmail(this->_email, message);
}

void Notify(INotifier& notifier, const std::string& message) {
	notifier.Notify(message);
}


int main() {
	SmsNotifier sms{ "+7-495-777-77-77" };
	EmailNotifier email{ "na-derevnyu@dedushke.ru" };

	Notify(sms, "I have White belt in C++");
	Notify(email, "And want a Yellow one");
	return 0;
}