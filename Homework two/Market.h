#pragma once

#include "Client.h"
#include "../Double linked list/DLList.h"
#include "../Queue with one link/Queue.h"
#include "MarketState.h"

class Market
{
public:
	Market(int NumberOfAllCashDecks); // max number of Decks (without the express one)
	void AddClient(Client * clients, int number); // add clients in the store (number - how many clients)
	struct MarketState getMarketState(); 
	// TO DO ClientState getClientState(int ID);
private:
	void processOneProduct();
	void addNewClients(Client * clients, int number);
	void addNewClientsIDs(Client * clients, int number);
private:
	DLList<Queue<Client*>> decks;
	Queue<Client*> expressDeck;
	size_t numberOfAllCashDecks;
	Queue<Client *> pendingQueue;
	static int id;
}; 