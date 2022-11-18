#include <iostream>
#include "avl_tree.hpp"
#include <cassert>

int main()
{
AVL<std::string> T;

T.insert_node("Gerhard", 0);
T.insert_node("Lidmila", 24);
T.insert_node("Dorian", 41);
T.delete_node("Dorian", 41);
T.insert_node("Palmiro", 7);
T.insert_node("Oto", 45);
T.delete_node("Gerhard", 0);
T.insert_node("Josef", 32);
T.delete_node("Oto", 45);
T.insert_node("Vidor", 49);
T.insert_node("Vladan", 45);
T.insert_node("Sibyla", 50);
T.insert_node("Eufrozina", 40);
T.insert_node("Radim", 6);
T.insert_node("Adriána", 13);
T.insert_node("Babeta", 42);
T.insert_node("Magdaléna", 46);
T.delete_node("Josef", 32);
T.insert_node("Danuta", 3);
T.delete_node("Palmiro", 7);
T.insert_node("Metod", 37);
T.delete_node("Eufrozina", 40);
T.insert_node("Šimona", 4);
T.insert_node("Ruben", 31);
T.insert_node("Koloman", 20);
T.insert_node("Augustin", 2);
T.delete_node("Šimona", 4);
T.insert_node("Tichomír", 19);
T.insert_node("Sotira", 48);
T.insert_node("Štefan", 27);
T.insert_node("Dobroslava", 19);
T.delete_node("Ruben", 31);
T.insert_node("Muriel", 27);
T.insert_node("Josefa", 18);
T.delete_node("Metod", 37);
T.insert_node("Amát", 0);
T.insert_node("Lydie", 37);
T.insert_node("Adriena", 6);
T.insert_node("Edgar", 46);
T.insert_node("Andělína", 24);
T.insert_node("Michael", 28);
T.insert_node("Hortensie", 13);
T.delete_node("Radim", 6);
T.insert_node("Kristina", 24);
T.insert_node("Arnošt", 13);
T.delete_node("Dobroslava", 19);
T.insert_node("Ofélie", 40);
T.insert_node("Ruprecht", 41);
T.delete_node("Sibyla", 50);
T.insert_node("Olivie", 16);
T.delete_node("Lidmila", 24);
T.insert_node("Zlatomíra", 43);
T.insert_node("Dionýz", 11);
T.delete_node("Vladan", 45);
T.insert_node("Florián", 9);
T.delete_node("Muriel", 27);
T.insert_node("Jakubka", 7);
T.delete_node("Hortensie", 13);
T.insert_node("Fatima", 37);
T.insert_node("Kasián", 0);
T.insert_node("Noemi", 34);
T.delete_node("Lydie", 37);
T.insert_node("Rita", 42);
T.insert_node("Romulus", 50);
T.insert_node("Faustina", 24);
T.insert_node("Ernest", 21);
T.insert_node("Penelopa", 36);
T.delete_node("Tichomír", 19);
T.insert_node("Matěj", 312);
T.printAllInfo();




}