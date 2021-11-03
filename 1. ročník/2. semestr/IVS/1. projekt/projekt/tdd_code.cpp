//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
// $Date:       $2021-03-08
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Iveta Snášelová
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
	m_pHead = nullptr;  //nastavení hlavičky na null - reprezentuje prázdnou frontu
}

PriorityQueue::~PriorityQueue()
{
	Element_t *el = GetHead();      //pomocný element
    	while(el != nullptr)           
    	{
        	Element_t *deleted = el;    //procházení seznamu a mazání prvek po prvku
        	el = el->pNext;
        	delete deleted;
    	}

    	m_pHead = nullptr;
}

void PriorityQueue::Insert(int value)
{
	Element_t *el = new Element_t();    //nastavení přidávaného prvku
    	el->value = value;
    	el->pNext = nullptr;

    	Element_t *help = GetHead();        //pomocný seznam

    	if(m_pHead == nullptr)      //seznam je prázdný
        	m_pHead = el;           //head nastavíme na vkládaný prvek (el->next = nullptr)
    	else
    	{
        	if(m_pHead->pNext == nullptr) //v seznamu je 1 prvek
        	{
            		if(m_pHead->value > value) //prvek v seznamu je větší než vkládaný
                		m_pHead->pNext = el;   //pořádí je v pořádku -> prvek zařadíme za
            		else
            		{
                		el->pNext = m_pHead;   //musím prvky prohodit, za vkládaný dám původní
                		m_pHead = el;         
            		}
        	}
        	else                //seznam obsahuje několik prvků
        	{
            		if(help->value <= value)    //vkládaný je největší -> dám jako hlavičku
            		{
                		el->pNext = help;       //za vkládaný přidám původní seznam
                		m_pHead = el;           //přepíšu hlavičku
                		return;
            		}
            		for(; help->pNext != nullptr; help = help->pNext)   //procházení seznamu
            		{                                             
                		if(help->pNext->value <= value)     //hledám prvek, který bude menší než vkládaný
                		{                                   //help->pNext->value, abych vkládaný mohla vložit před najítý
                    			el->pNext = help->pNext;
                    			help->pNext = el;
                    			return;
                		}
            		}           
            		el->pNext=nullptr;  //vkládaný je nejmenší -> vložím na konec seznamu
            		help->pNext = el;
        	}
    	}
}

bool PriorityQueue::Remove(int value)
{
	Element_t *start = GetHead();
    	Element_t *deleted = NULL;

    	if(start == NULL)    //seznam je prázdný, není co mazat
        	return false;
    
    	if(start->pNext == NULL)    //seznam má 1 prvek
    	{
        	if(start->value == value)   //právě ten jediný prvek chci smazat
        	{
            		m_pHead = NULL;         //mám opět prázdný seznam
            		delete start;
            		return true;
        	}
        	else                //seznam má 1 prvek, ale ne správný
            		return false;
    	}
    	else                    //seznam má více prvků
    	{
        	if(start->value == value) //mazaný je první prvek v seznamu
        	{
            		deleted = start;
            		start = start->pNext;
            		m_pHead = start;        //přenastavení odkazu na hlavičku

            		delete deleted;
            		return true;
        	}
        	else        //mazaný je někde uprostřed seznamu
        	{
            		while(start->pNext->pNext != NULL)  //seznam má víc prvků
            		{                                 
                		if(start->pNext->value == value)    //našla jsem mazaný prvek
                		{                           
                      			deleted = start->pNext;
                      			start->pNext = start->pNext->pNext;     //přenastavení odkazu - "vynechání" mazaného prvku
            
                    			delete deleted;
                    			return true;
                		}
                		start = start->pNext;
            		}
            		if(start->pNext->value == value)   //mazaný prvek je poslední
            		{
                		deleted = start->pNext;
                		start->pNext = NULL;

                		delete deleted;
                		return true;
            		}
        	}
    	}
    	return false;   //prvek není v seznamu
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
	for(Element_t *start = GetHead(); start != nullptr; start = start->pNext)   //procházení seznamu
        	if (start->value == value)   //nalezení hledaného prvku
            		return start;
    	return NULL;
}

size_t PriorityQueue::Length()
{
	size_t length = 0;  //seznam je prázdný -> délka = 0
    	for(Element_t *start = GetHead(); start != nullptr; start = start->pNext)   //procházení seznamu
        	length++;        //každá iterace zvětší délku

	return length;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
