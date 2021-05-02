void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, amount;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // ????? ? ?????
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

		case "carpenter_17":
            dialog.text = "Orders, captain?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Yes. Your captain's treasures have been found. He did hide them well but I have outsmarted him!";
				link.l1.go = "carpenter_18";
				break;
			}
			link.l2 = "Rodgar, my ship is need for repairs. Are you and your guys ready?";
			link.l2.go = "repair";
			link.l3 = "Rodgar, I'd like to leave one of my ships here.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, I'd like to take one of my ships back.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Look, is there any empty building I could use as a storehouse?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, I want to see a storehouse.";
				link.l5.go = "storadge_3";
			}
			if (!CheckAttribute(npchar, "manoir") && !CheckAttribute(npchar, "manoir_money"))
			{
			link.l6 = "Rodgar, j'ai un grand projet pour cette île. Nous allons bâtir un immence manoir !";
			link.l6.go = "manoir_construct";
			}
			if (CheckAttribute(npchar, "manoir"))
			{
			link.l6 = "Rodgar, où en sommes nous avec la construction.";
			link.l6.go = "manoir";
			}				
			if (CheckAttribute(npchar, "manoir_money") && makeint(Pchar.money) >= 5000000)
			{
			link.l6 = "Je vous apporte votre 'prime' pour la construction du manoir, Rodgar";
			link.l6.go = "manoir_construct5";
			}		
			if (CheckAttribute(npchar, "manoir.part"))
			{
			link.l6 = "J'aimerais agrandir le manoir";
			link.l6.go = "manoir_part";
			}	
			link.l7 = "Test";
			link.l7.go = "test";			
			link.l99 = "Nothing yet...";
			link.l99.go = "carpenter_exit";
		break;

		case "test":
			DialogExit();
			LaunchManorScreen();	
		break;		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "carpenter_exit":
			if(npchar.location == "MyOwn_Tavern") 
			{
				DialogExit();
				npchar.dialog.currentnode = "carpenter_17";
				LAi_SetActorType(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "MyOwn_Manor", "goto", "goto12", "Manor_Build_Life", -1);				
				break;			
			}		
            DialogExit();
			LAi_SetWarriorType(npchar);
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Congratulations cap. What do we do next? Are we leaving?";
			link.l1 = "Have you been here for long?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "For too long. It's been a year since Wulfric put me in charge here.";
			link.l1 = "I have decided that this secret base is too good to be wasted. The village is mine now. I can leave you and your men here if you want. Rum, provisions, medicine - all yours.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "That would great captain. I got used to life on this beach, this island.";
			link.l1 = "Splendid. By the way, what's the island's name?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Perhaps one day we will build more houses and structures... But later. Right now you will keep the same role here but under different captain.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Deal. You just take care of yourself captain and don't forget supplying us with provisions.";
			link.l1 = "Sure thing Rodgar. Good luck, I should sail to La Vega.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;

		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "By all means, captain! All we need are planks and sailcloth. Go to you landing location and order the crew to prepare materials.";
				link.l1 = "On my way. Do it fast.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Sure, captain, but in my understanding you don't need it.";
				link.l1 = "Just asking...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "It's possible, captain. A few limitations though: there are only two places on this island suitable for this.  Also you can't leave here anyone but a single officer to each ship. We simply don't have enough resources to keep crews here. Yet. Finally, there is no room for first ranked ships.";
			link.l1 = "Got it. I am ready to leave a ship here.";
			link.l1.go = "shipstock";
			link.l2 = "Very well, I will get her ready.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if (sti(npchar.portman) == 2)
			{
				dialog.text = "Captain, there is no more room for another ship.";
				link.l1 = "Right...";
				link.l1.go = "carpenter_exit";
				break;
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Captain, you have only one ship.";
				link.l1 = "Hm... I should drink less...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "What ship do you want to leave here?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Wait, I have changed my mind.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				dialog.text = "Captain, first ranks are too big for our shores. I've told you that already.";
				Link.l1 = "Right.";
				Link.l1.go = "carpenter_exit";
				break;
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = "Captain, take all of her crew to your flagship except an officer.";
				Link.l1 = "Ah, right! Will do that!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "So, we are to keep here a"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" named '"+chref.Ship.Name+"'. Right?";
			Link.l1 = "Right.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = "Very well, we'll see her delivered to a safe harbor.";
			Link.l1 = "Splendid!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Which ship are you going to take, captain?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Wait, I have changed my mind.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Captain, you don't have room in your squadron for one more ship.";
				link.l1 = "Hm. You're right.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "Are you taking her?";
			link.l1 = "Yes.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Wait, I have changed my mind.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Here? No. But Wulfric had built a huge barn not far from here. A solid building, well covered with palm leaves and tarred sailcloth. It has a lock and a room for a cargo enough to fill a dozen of trade ships\nIt's empty now, but I have a key if you want to examine it. Shall we?";
			link.l1 = "Sure! By the way: what of rats on this island? Will they spoil my goods in the barn?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Wolf had it covered it too: he brought two cats here from the mainland. He forgot about males though, so these crazy furred bitches make lousy sounds every time their season comes. But they hunt mice and rats pretty well. Don't worry about it, captain. Your goods will be safe from rats and winds.";
			link.l1 = "Great! I will make a use of it. Keep your key to yourself and show me this storehouse.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";			
			if(!CheckAttribute(npchar, "storadge"))
			{
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			}						
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Follow me, captain.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;		
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MANOIR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "manoir_construct":
            dialog.text = "Un manoir !? Mais capitaine vous n'êtes pas sérieux ? J'ai travaillé sur ce type de chantiers dans une autre vie, et l'éttendu des travaux est pharamineuse, sans parler de la quantité de matériaux nécessaire...";
			link.l1 = "Vous semblez vous y connaître. Je vous apporterai tout ce dont vous avez besoin et la construction prendra le temps nécessaire.";
			link.l1.go = "manoir_construct1";
		break;
		
		case "manoir_construct1":
            dialog.text = "Bien, je vois que vous semblez être décidé. Moi et les gars tâcherons de faire de notre mieux... Par où commencer ? Hmm... Je pense pouvoir me débrouiller avec le plan de la batisse, de vieux souvenirs pourraient remonter. Pour les matériaux, je ne suis pas encore certain des quantités. Je pense qu'il nous faudra au moins 10000 unités de briques, 8000 de planches et 6000 d'outils. Et puis dans un second temps, nous aurons besoin de mains d'oeuvres, à trois vous pensez bien... Une centaine d'esclave devrait suffire pour finir les travaux en 3 mois. Il nous faudra assez de ration pour tenir durant ce temps, soit environ 300 unités.";
			link.l1 = "On dirait que vous savez dans quoi vous vous embarquez. Dès que j'aurai levé les voiles, je commencerai à réunir les matériaux.";
			link.l1.go = "manoir_construct2";
		break;		

		case "manoir_construct2":
            dialog.text = "Autre chose capitaine. Mon travail ici n'est pas vraiment de gérer un chantier de construction. Aussi je voudrai une petite compensation pour mes efforts.";
			link.l1 = "Je pense que je vous la dois, de combien parlons nous ?";
			link.l1.go = "manoir_construct3";
		break;

		case "manoir_construct3":
            dialog.text = "De 5 000 000 pesos mon capitaine.";
			link.l1 = "Vous plaisentez j'espère.";
			link.l1.go = "manoir_construct4";
		break;		
		
		case "manoir_construct4":
			npchar.manoir_money = true;
            dialog.text = "Hélas capitaine, je veux exactement recevoir cette somme. Je sais que vous ne mettrez pas longtemps à réunir cette argent. Vous pouvez toujours essayer de trouver un vrai architecte, mais ils ne vous demanderont pas moins.";
			if (makeint(Pchar.money) >= 5000000)
			{
			link.l1 = "Bon très bien, voici vos pièces, faîtes en bon usage.";
			link.l1.go = "manoir_construct5";
			}
			else
			{
			link.l2 = "Bon, c'est entendu. Je vous raménnerez la somme.";
			link.l2.go = "carpenter_exit";
			}
		break;	

		case "manoir_construct5":
            dialog.text = "Merveilleux, vous pouvez à présent commencer à acheminer les matériaux.";
			link.l1 = "Splandide !";
			link.l1.go = "carpenter_exit";
			DeleteAttribute(npchar, "manoir_money");
			addMoneyToCharacter(pchar, -5000000);
			npchar.manoir = true;
			npchar.manoir.material = true;
			npchar.manoir.material.briq = 10000;
			npchar.manoir.material.wood = 8000;
			npchar.manoir.material.tool = 6000;		
		break;	

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		
		case "manoir":
			if (CheckAttribute(npchar, "manoir.material"))
			{			
				amount = GetSquadronGoods(Pchar, GOOD_BRICK) - sti(npchar.manoir.material.briq);
				if (amount < 0)
				{
					amount = amount + sti(npchar.manoir.material.briq);
				}
				else
				{
					amount = sti(npchar.manoir.material.briq);
				}
				RemoveCharacterGoods(Pchar, GOOD_BRICK, amount);
				npchar.manoir.material.briq = sti(npchar.manoir.material.briq) - amount;
				
				amount = GetSquadronGoods(Pchar, GOOD_PLANKS) - sti(npchar.manoir.material.wood);
				if (amount < 0)
				{
					amount = amount + sti(npchar.manoir.material.wood);
				}
				else
				{
					amount = sti(npchar.manoir.material.wood);
				}
				RemoveCharacterGoods(Pchar, GOOD_PLANKS, amount);
				npchar.manoir.material.wood = sti(npchar.manoir.material.wood) - amount;
				
				if(sti(npchar.manoir.material.briq) < 1 && sti(npchar.manoir.material.wood) < 1)
				{
					dialog.text = "Très bien, vous avez réunis tous les matériaux de construction nécessaire. Maintenant il vous faut réunir de la main d'oeuvre. Environ 100 esclaves seraient suffisant pour finir les travaux en 3 mois. Et apportez 300 unités de ration pour la soupe.";
					link.l1 = "Je m'en occupe.";
					link.l1.go = "carpenter_exit";
					DeleteAttribute(npchar, "manoir.material");
					DeleteAttribute(npchar, "manoir.material.briq");
					DeleteAttribute(npchar, "manoir.material.wood");
					DeleteAttribute(npchar, "manoir.material.tool");	
					npchar.manoir.slave = true;
					npchar.manoir.slave.slave = 100;
					npchar.manoir.slave.food = 300;
					break;
				}
				else
				{
					dialog.Text = "Très bien, il nous faudrait encore " + sti(npchar.manoir.material.briq) +" untités de briques et " + sti(npchar.manoir.material.wood)+ " unités de planches";
					link.l1 = "Je vais tacher d'en ramener.";
					link.l1.go = "carpenter_exit";
				}				
			}
			if (CheckAttribute(npchar, "manoir.slave"))
			{			
				amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(npchar.manoir.slave.slave);
				if (amount < 0)
				{
					amount = amount + sti(npchar.manoir.slave.slave);
				}
				else
				{
					amount = sti(npchar.manoir.slave.slave);
				}
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
				npchar.manoir.slave.slave = sti(npchar.manoir.slave.slave) - amount;
				
				amount = GetSquadronGoods(Pchar, GOOD_FOOD) - sti(npchar.manoir.slave.food);
				if (amount < 0)
				{
					amount = amount + sti(npchar.manoir.slave.food);
				}
				else
				{
					amount = sti(npchar.manoir.slave.food);
				}
				RemoveCharacterGoods(Pchar, GOOD_FOOD, amount);
				npchar.manoir.slave.food = sti(npchar.manoir.slave.food) - amount;				
				if(sti(npchar.manoir.slave.slave) < 1 && sti(npchar.manoir.slave.food) < 1)
				{
					dialog.text = "Capitaine tout est en oredre pour démarer la construction, nous allons déblayer la place et commencer sans plus attendre, il nous faudra 3 mois.";
					link.l1 = "Mazette, j'attendrai avec impatience !";
					link.l1.go = "carpenter_startconstruct";				
				}
				else
				{
					dialog.Text = "Très bien, amenez encore " + sti(npchar.manoir.slave.slave) + " esclaves et " + sti(npchar.manoir.slave.food) + " rations.";
					link.l1 = "Je vais tacher d'en ramener.";
					link.l1.go = "carpenter_exit";
				}				
			}	
			if (CheckAttribute(npchar, "manoir.construct"))
			{
				dialog.text = "Les travaux seront finis dans peu de temps";
				link.l1 = "Fort bien.";
				link.l1.go = "carpenter_exit";
				break;
			}
		break;		

		case "carpenter_startconstruct":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			DeleteAttribute(npchar, "manoir.slave");
			DeleteAttribute(npchar, "manoir.slave.slave");
			DeleteAttribute(npchar, "manoir.slave.food");
			npchar.manoir.construct = true;
			DoQuestReloadToLocation("Islamona_jungle_01","goto","ass4", "Manoirbuild");
		break;	

		case "manoir_finish_construct":
            dialog.text = "C'est fini";
			link.l1 = "sans as";
			link.l1.go = "carpenter_17";
			npchar.room.etage.nb = 4;
			npchar.room.rdc.nb = 6;			
		break;	

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		

		case "manoir_part":
			if (CheckAttribute(npchar, "room.construct"))
			{
				dialog.text = "Les travaux seront finis dans peu de temps";
				link.l1 = "Yes";
				link.l1.go = "carpenter_exit";
				break;
			}		
            dialog.text = "Que voulez-vous construire ?";
			if (!CheckAttribute(npchar, "have.plantation"))
			{
			link.l1 = "Plantation";
			link.l1.go = "Plantation";
			}
			if (sti(npchar.room.etage.nb)>1)
			{
			link.l2 = "Allons voir à l'étage";
			link.l2.go = "Etage";
			}
			if (sti(npchar.room.rdc.nb)>4)
			{
			link.l3 = "Concentrons-nous sur le rez de chaussé";
			link.l3.go = "Rdc";
			}
			if (CheckAttribute(npchar, "have.tavern")) {if (sti(npchar.tavern.etage.nb) != 2 || !CheckAttribute(npchar, "have.tavern.etage"))
			{
			link.l4 = "Compléter tavern";
			link.l4.go = "Complete_tavern_1";
			}}
			if (CheckAttribute(npchar, "have.brothel") && !CheckAttribute(npchar, "have.redroom"))
			{
			link.l5 = "Compléter brothel";
			link.l5.go = "Redroom";
			}
			if (CheckAttribute(npchar, "have.dungeon") && !CheckAttribute(npchar, "have.torture"))
			{
			link.l6 = "Compléter dongeon";
			link.l6.go = "Torture";
			}			
			link.l99 = "Rien pour le moment";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Etage":
            dialog.text = "Suivez-moi";					
			link.l1 = "Ok";
			link.l1.go = "Etage_exit";	
		break;	

		case "Etage_exit":
            DialogExit();
			npchar.dialog.currentnode = "Etage_build";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload"+npchar.room.etage.nb, "MyOwn_Manor", "reload", "reload"+npchar.room.etage.nb, "Manor_Build_Life", -1);
		break;		
	
		case "Etage_build":
            dialog.text = "Que voulez-vous construire ?";			
			if (!CheckAttribute(npchar, "have.bedroom"))
			{
			link.l1 = "Bedroom";
			link.l1.go = "Bedroom";
			}
			if (!CheckAttribute(npchar, "have.office"))
			{
			link.l2 = "Office";
			link.l2.go = "Office";
			}
			if (!CheckAttribute(npchar, "have.bank"))
			{
			link.l3 = "Bank";
			link.l3.go = "Bank";
			}	
			if (!CheckAttribute(npchar, "have.depot"))
			{
			link.l4 = "Depot";
			link.l4.go = "Depot";
			}	
			link.l99 = "Rien pour le moment";
			if(npchar.location != "MyOwn_Tavern") 
			{
			link.l99.go = "carpenter_exit";	
			}
			else
			{
			link.l99.go = "Complete_tavern_3";	
			}						
		break;

		case "Rdc":
            dialog.text = "Suivez-moi";					
			link.l1 = "Ok";
			link.l1.go = "Rdc_exit";	
		break;	

		case "Rdc_exit":
            DialogExit();
			npchar.dialog.currentnode = "Rdc_build";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload"+npchar.room.rdc.nb, "MyOwn_Manor", "reload", "reload"+npchar.room.rdc.nb, "Manor_Build_Life", -1);
		break;			

		case "Rdc_build":
            dialog.text = "Que voulez-vous construire ?";			
			if (!CheckAttribute(npchar, "have.prison"))
			{
			link.l1 = "Prison";
			link.l1.go = "Prison";
			}
			if (!CheckAttribute(npchar, "have.tavern"))
			{
			link.l2 = "Tavern";
			link.l2.go = "Tavern";
			}
			if (!CheckAttribute(npchar, "have.dungeon"))
			{
			link.l3 = "Dungeon";
			link.l3.go = "Dungeon";
			}
			if (!CheckAttribute(npchar, "have.brothel"))
			{
			link.l4 = "Brothel";
			link.l4.go = "Brothel";
			}				
			link.l99 = "Rien pour le moment";
			if(npchar.location != "MyOwn_Tavern") 
			{
			link.l99.go = "carpenter_exit";	
			}
			else
			{
			link.l99.go = "Complete_tavern_3";	
			}			
		break;

		case "Complete_tavern_1":
            dialog.text = "Suivez-moi";					
			link.l1 = "Ok";
			link.l1.go = "Complete_tavern_2";	
		break;	

		case "Complete_tavern_2":
            DialogExit();
			npchar.dialog.currentnode = "Complete_tavern_3";
			LAi_SetActorType(npchar);
			if (locations[FindLocation("MyOwn_Manor")].reload.l7.name == "reload5")
			{
			LAi_ActorGoToLocation(npchar, "reload", "reload5", "MyOwn_Tavern", "goto", "goto4", "Manor_Build_Life", -1);
			}
			else
			{
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "MyOwn_Tavern", "goto", "goto4", "Manor_Build_Life", -1);
			}			
		break;		
	
		case "Complete_tavern_3":
            dialog.text = "Que voulez-vous construire ?";	
			if (!CheckAttribute(npchar, "have.tavern.etage"))
			{
			link.l1 = "Etage";
			link.l1.go = "Etage_build";
			}
			if (sti(npchar.tavern.etage.nb) == 4)
			{
			link.l2 = "A ma droite";
			link.l2.go = "Rdc_build";			
			}
			if (sti(npchar.tavern.etage.nb) == 3)
			{
			link.l2 = "Derrière vous";
			link.l2.go = "Rdc_build";			
			}
			link.l99 = "Rien pour le moment";
			link.l99.go = "carpenter_exit";				
		break;
	
		case "Plantation":
            dialog.text = "Bien, l'ajout d'une plantation vous coutera 1 000 000 piastres...";
			if (sti(pchar.Money) > 1000000)
            {						
			link.l1 = "Ok";
			link.l1.go = "Plantation_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "manoir_part";
		break;			
		
		case "Plantation_Build":   
  			dialog.text = "Bien, votre plantation seras prête dans 30 jours !Notez que vous devrez vous rendre dans le bureau de la plantation et y disposer un officier afin d'utilisé celle-ci...";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-1000000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 30);
            PChar.quest.MyBuild.function	= "MyPlantationBuild";	

			if(!CheckAttribute(npchar, "storadge"))
			{
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			}
        break;	

		case "Bedroom":
            dialog.text = "Très bien, l'ajout de votre chambre vous coutera 150 000 piastres...";
			if (sti(pchar.Money) > 150000)
            {						
			link.l1 = "Allez-y pour ma chambre !";
			link.l1.go = "Bedroom_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "Etage_build";
		break;	

		case "Bedroom_Build":   
  			dialog.text = "Très bien, dans 10 jours votre chambre seras prête !";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-150000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
            PChar.quest.MyBuild.function	= "MyBedroomBuild";	
			if(npchar.location == "MyOwn_Tavern") npchar.ImOnTavern = true;
        break;	

		case "Office":
            dialog.text = "Très bien, l'ajout de votre bureau vous coutera 250 000 piastres...";
			if (sti(pchar.Money) > 250000)
            {						
			link.l1 = "Allez-y pour mon bureau !";
			link.l1.go = "office_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "Etage_build";
		break;	

		case "Office_Build":   
  			dialog.text = "Très bien, dans 10 jours votre bureau seras prêt !";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-250000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
            PChar.quest.MyBuild.function	= "MyOfficeBuild";	
			if(npchar.location == "MyOwn_Tavern") npchar.ImOnTavern = true;			
        break;	

		case "Bank":
            dialog.text = "La construction d'un bureau de trésorerie vous coutera 500 000 piastres...";
			if (sti(pchar.Money) > 500000)
            {						
			link.l1 = "Voici l'argent !";
			link.l1.go = "bank_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "Etage_build";
		break;	

		case "Bank_Build":   
  			dialog.text = "Dans 10 jours votre trésorerie seras prête !";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-500000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
            PChar.quest.MyBuild.function	= "MyBankBuild";			
			if(npchar.location == "MyOwn_Tavern") npchar.ImOnTavern = true;			
        break;		

		case "Depot":
            dialog.text = "L'aménagement d'un dépot coutera la somme de 250 000 piastres...";
			if (sti(pchar.Money) > 250000)
            {						
			link.l1 = "Allons-y avec le dépot !";
			link.l1.go = "Depot_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "Etage_build";
		break;	

		case "Depot_Build":   
  			dialog.text = "Dans 10 jours votre dépot seras prêt !";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-250000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
            PChar.quest.MyBuild.function	= "MyDepotBuild";	
			if(npchar.location == "MyOwn_Tavern") npchar.ImOnTavern = true;		

			if(!CheckAttribute(npchar, "storadge"))
			{
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			}		
        break;		

		case "Prison":
            dialog.text = "La construction d'une prison vous coutera la somme de 1 500 000 piastres...";
			if (sti(pchar.Money) > 1500000)
            {						
			link.l1 = "Voici l'argent !";
			link.l1.go = "Prison_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "Rdc_build";
		break;	

		case "Prison_Build":   
  			dialog.text = "Très bien, votre prison seras prête dans 30 jours !";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-1500000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 30);
            PChar.quest.MyBuild.function	= "MyPrisonBuild";	
			if(npchar.location == "MyOwn_Tavern") npchar.ImOnTavern = true;			
        break;	

		case "Tavern":
            dialog.text = "La construction d'une taverne vous coutera la somme de 1 500 000 piastres...";
			if (sti(pchar.Money) > 1500000)
            {						
			link.l1 = "Voici l'argent !";
			link.l1.go = "Tavern_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "Rdc_build";
		break;	

		case "Tavern_Build":   
  			dialog.text = "Très bien, votre taverne seras prête dans 30 jours !";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-1500000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 30);
            PChar.quest.MyBuild.function	= "MyTavernBuild";		
        break;

		case "Dungeon":
            dialog.text = "il vous en couteras 2 500 000 piastres...";
			if (sti(pchar.Money) > 2500000)
            {						
			link.l1 = "Voici l'argent !";
			link.l1.go = "Dungeon_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "Rdc_build";
		break;	

		case "Dungeon_Build":   
  			dialog.text = "Très bien, les travaux seront complété d'ici 30 jours !";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-2500000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 30);
            PChar.quest.MyBuild.function	= "MyDungeonBuild";
			if(npchar.location == "MyOwn_Tavern") npchar.ImOnTavern = true;			
        break;	

		case "Brothel":
            dialog.text = "L'ajout d'un bordel vous coutera la somme de 1 500 000 piastres...";
			if (sti(pchar.Money) > 1500000)
            {						
			link.l1 = "Voici l'argent !";
			link.l1.go = "Brothel_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "Rdc_build";
		break;	

		case "Brothel_Build":   
  			dialog.text = "Très bien !Votre bordel seras prêt dans 30 jours...";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-1500000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 30);
            PChar.quest.MyBuild.function	= "MyBrothelBuild";	
			if(npchar.location == "MyOwn_Tavern") npchar.ImOnTavern = true;			
        break;		

		case "Torture":
            dialog.text = "La construction d'une tel pièce vous coutera 2 000 000 de piastres...";
			if (sti(pchar.Money) > 2000000)
            {						
			link.l1 = "Voici l'argent !";
			link.l1.go = "Torture_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "manoir_part";
		break;	

		case "Torture_Build":   
  			dialog.text = "Très bien, votre chambre aux tortures seras complété d'ici 30 jours !";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-2000000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 30);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 30);
            PChar.quest.MyBuild.function	= "MyTortureBuild";			
        break;	

		case "Redroom":
            dialog.text = "Très bien, l'ajout de votre chambre vous coutera 150 000 piastres...";
			if (sti(pchar.Money) > 150000)
            {						
			link.l1 = "Allez-y pour ma chambre !";
			link.l1.go = "Redroom_Build";	
	        }
			link.l2 = "Voyons ce que vous proposez d'autre.";
			link.l2.go = "manoir_part";
		break;	

		case "Redroom_Build":   
  			dialog.text = "Très bien, dans 10 jours votre chambre seras prête !";
			link.l1.go = "carpenter_exit";
			AddMoneyToCharacter(pchar,-150000);
			npchar.room.construct = true;				
			PChar.quest.MyBuild.win_condition.l1            = "Timer";
            PChar.quest.MyBuild.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
            PChar.quest.MyBuild.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
            PChar.quest.MyBuild.function	= "MyRedroomBuild";			
        break;			
	}
	
}
