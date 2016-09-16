/*#include "EventManager.h"
#include "EventData.h"
#include "GenericDelegate.h"

class EventReceiverA{
public:
	EventReceiverA(){
	}
	~EventReceiverA() {
		cout << "Destructor A\n";
	}

	void OnEvent( EventData *par_evtdata ){
		cout << "Event Received in Class A\n";
	}
};

class EventReceiverB{
public:
	EventReceiverB(){
	}
	~EventReceiverB() {
		cout << "Destructor B\n";
	}
	void OnEvent(EventData *par_evtdata){
		cout << "Event Received in Class B\n";
	}
};

int main(int argc, char *argv[]) {

	EventReceiverA *a = new EventReceiverA();
	EventReceiverB *b = new EventReceiverB();

	auto em = new EventManager();
	
	cout << "Lets try to add 2 different listeners and raise the event\n";
	em->addEventListener("test", GenericDelegate::create <EventReceiverA, &EventReceiverA::OnEvent>(a));
	em->addEventListener("test", GenericDelegate::create <EventReceiverB, &EventReceiverB::OnEvent>(b));
	
	em->dispacthEvent("test", new EventData(0, "aa"));
	cin.get();
	
	
	cout << "Lets try to remove B class listener, and raise the 'test' event\n";
	
	em->removeEventListener("test", typeid(EventReceiverB).name());
	em->dispacthEvent("test", new EventData(0, "aa"));
	cin.get();

	delete em;
	// All 
	cin.get();
	return 0;	
}

*/