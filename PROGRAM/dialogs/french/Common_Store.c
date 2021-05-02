// boal 08/04/04 общий диалог торговцев
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "SD\TEXT\DIALOGS\Common_Store.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], "Courrez, "+ GetSexPhrase("l'ami","l'amie") +DLG_TEXT_BASE[2]), 
					LinkRandPhrase("Qu'est-ce que vous voulez, "+ GetSexPhrase("crapule","salope") +DLG_TEXT_BASE[3]+ GetSexPhrase("sale pirate","sale tueuse") +" !", DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[11]));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[458], DLG_TEXT_BASE[459]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[460], DLG_TEXT_BASE[461]);
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = DLG_TEXT_BASE[462]; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = DLG_TEXT_BASE[463]; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = DLG_TEXT_BASE[464]; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = DLG_TEXT_BASE[41];
				Link.l1 = DLG_TEXT_BASE[42];
				Link.l1.go = "trade_1";
				Link.l2 = DLG_TEXT_BASE[24];
				Link.l2.go = "quests";
				Link.l3 = DLG_TEXT_BASE[16];
				Link.l3.go = "exit";
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = DLG_TEXT_BASE[43];
				Link.l1 = DLG_TEXT_BASE[77];
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = DLG_TEXT_BASE[465];
				Link.l1 = DLG_TEXT_BASE[466];
				Link.l1.go = "trial";
				break;
			}
			
            dialog.Text = GetNatPhrase(npchar, LinkRandPhrase(DLG_TEXT_BASE[23],DLG_TEXT_BASE[27],DLG_TEXT_BASE[31]), LinkRandPhrase(DLG_TEXT_BASE[25],DLG_TEXT_BASE[26],DLG_TEXT_BASE[28]), LinkRandPhrase(DLG_TEXT_BASE[22],DLG_TEXT_BASE[29],DLG_TEXT_BASE[30]),LinkRandPhrase(DLG_TEXT_BASE[32],DLG_TEXT_BASE[33],DLG_TEXT_BASE[34]));
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[35]+GetFullName(pchar)+DLG_TEXT_BASE[36],DLG_TEXT_BASE[35]+GetFullName(pchar)+DLG_TEXT_BASE[37]+pchar.ship.name+DLG_TEXT_BASE[40],GetFullName(pchar)+DLG_TEXT_BASE[38]+pchar.ship.name+DLG_TEXT_BASE[39]);
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], "Courrez, "+ GetSexPhrase("l'ami","l'amie") +DLG_TEXT_BASE[2]), 
					LinkRandPhrase("Qu'est-ce que vous voulez, "+ GetSexPhrase("crapule","salope") +DLG_TEXT_BASE[3]+ GetSexPhrase("sale pirate","sale tueuse") +" !", DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[11]));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = DLG_TEXT_BASE[467]; ;
				link.l1 = link.l13 = DLG_TEXT_BASE[468]; ;
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = DLG_TEXT_BASE[43];
				Link.l1 = DLG_TEXT_BASE[77];
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = DLG_TEXT_BASE[465];
				Link.l1 = DLG_TEXT_BASE[466];				
				Link.l1.go = "trial";
				break;
			}
            
			dialog.text = NPCharRepPhrase(npchar,
			                 pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[121], DLG_TEXT_BASE[122], DLG_TEXT_BASE[123]) +GetFullName(pchar)+"! "
							                 + LinkRandPhrase(DLG_TEXT_BASE[124],DLG_TEXT_BASE[125], DLG_TEXT_BASE[126])
											  + RandPhraseSimple(DLG_TEXT_BASE[127], DLG_TEXT_BASE[128]),
							                LinkRandPhrase(DLG_TEXT_BASE[129], DLG_TEXT_BASE[130], DLG_TEXT_BASE[131]) + DLG_TEXT_BASE[132]
											+ RandPhraseSimple(DLG_TEXT_BASE[133],DLG_TEXT_BASE[134])+DLG_TEXT_BASE[135]+ RandPhraseSimple(DLG_TEXT_BASE[136],DLG_TEXT_BASE[137])
											+ LinkRandPhrase(DLG_TEXT_BASE[138],DLG_TEXT_BASE[139], DLG_TEXT_BASE[140])+RandPhraseSimple(DLG_TEXT_BASE[141], DLG_TEXT_BASE[142])),
							 pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[143],DLG_TEXT_BASE[144],DLG_TEXT_BASE[145]) + GetFullName(pchar)
							 				+ LinkRandPhrase(DLG_TEXT_BASE[146],DLG_TEXT_BASE[147],DLG_TEXT_BASE[148])
											 +LinkRandPhrase(DLG_TEXT_BASE[149],DLG_TEXT_BASE[150], DLG_TEXT_BASE[151]),
							                DLG_TEXT_BASE[152] +GetFullName(pchar)+ LinkRandPhrase(DLG_TEXT_BASE[153],
											DLG_TEXT_BASE[154],DLG_TEXT_BASE[155]) +DLG_TEXT_BASE[156]));

			link.l1 = NPCharRepPhrase(npchar,
			            pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[157], DLG_TEXT_BASE[158],DLG_TEXT_BASE[159])
									  +LinkRandPhrase(DLG_TEXT_BASE[160],DLG_TEXT_BASE[161],DLG_TEXT_BASE[162]) +DLG_TEXT_BASE[163]
									  +LinkRandPhrase(DLG_TEXT_BASE[164],DLG_TEXT_BASE[165], DLG_TEXT_BASE[166]),
						               LinkRandPhrase(DLG_TEXT_BASE[167],DLG_TEXT_BASE[168],DLG_TEXT_BASE[169]) + GetAddress_FormToNPC(NPChar)+" " +GetFullName(Npchar)
									   +RandPhraseSimple(DLG_TEXT_BASE[170],DLG_TEXT_BASE[171])
									   +LinkRandPhrase(DLG_TEXT_BASE[172], DLG_TEXT_BASE[173], DLG_TEXT_BASE[174])+ "."),
						pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[175],DLG_TEXT_BASE[176]) +GetFullName(Npchar)+ "! "
						              +LinkRandPhrase(DLG_TEXT_BASE[177], DLG_TEXT_BASE[178],DLG_TEXT_BASE[179])
						              +RandPhraseSimple(DLG_TEXT_BASE[180],DLG_TEXT_BASE[181]),
						               DLG_TEXT_BASE[182] + GetAddress_FormToNPC(NPChar)+ DLG_TEXT_BASE[183] + LinkRandPhrase(DLG_TEXT_BASE[184],
									    DLG_TEXT_BASE[185], DLG_TEXT_BASE[186])));
										link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,
			                                         pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[187],DLG_TEXT_BASE[188]) +LinkRandPhrase("Que vient faire un "+ GetSexPhrase("gentleman","gentleman, oh, excusez moi - une lady") +DLG_TEXT_BASE[189],
													                                 DLG_TEXT_BASE[190], DLG_TEXT_BASE[191]),
            														LinkRandPhrase(DLG_TEXT_BASE[192], DLG_TEXT_BASE[193],DLG_TEXT_BASE[194])+RandPhraseSimple(DLG_TEXT_BASE[195],DLG_TEXT_BASE[196])
																	+LinkRandPhrase(DLG_TEXT_BASE[197],DLG_TEXT_BASE[198],DLG_TEXT_BASE[199])
																	+RandPhraseSimple(DLG_TEXT_BASE[200],DLG_TEXT_BASE[201])+DLG_TEXT_BASE[202]),
													 pcharrepphrase(RandPhraseSimple("Des marchandises pour "+ GetSexPhrase("les gentlemens","les gentlemens et ladies") +DLG_TEXT_BASE[203],
													                                 DLG_TEXT_BASE[204]),
                 												DLG_TEXT_BASE[205] +LinkRandPhrase(DLG_TEXT_BASE[206] + NationNameGenitive(sti(NPChar.nation)),DLG_TEXT_BASE[207], DLG_TEXT_BASE[208])
																	+RandPhraseSimple(DLG_TEXT_BASE[209],DLG_TEXT_BASE[210])
																	+RandPhraseSimple(DLG_TEXT_BASE[211],DLG_TEXT_BASE[212]) +DLG_TEXT_BASE[213])),
				                                  NPCharRepPhrase(npchar,
												  	 pcharrepphrase(DLG_TEXT_BASE[214],
													                DLG_TEXT_BASE[215]+ GetSexPhrase(" petit malin","e petite maline") +". " +RandPhraseSimple(DLG_TEXT_BASE[216]+ GetSexPhrase("un vrai heros","une vraie casse-cou") +".", DLG_TEXT_BASE[217]
																	+RandPhraseSimple(DLG_TEXT_BASE[218], DLG_TEXT_BASE[219]))),
													 pcharrepphrase(DLG_TEXT_BASE[220],
													                DLG_TEXT_BASE[221] + GetFullName(pchar)+DLG_TEXT_BASE[222])),
												  NPCharRepPhrase(npchar,
												     RandPhraseSimple(DLG_TEXT_BASE[223] ,
													   RandPhraseSimple(DLG_TEXT_BASE[224],DLG_TEXT_BASE[225]) +DLG_TEXT_BASE[226])
													   +RandPhraseSimple(DLG_TEXT_BASE[227], DLG_TEXT_BASE[228]),
													 pcharrepphrase(DLG_TEXT_BASE[229] + GetFullName(pchar)+DLG_TEXT_BASE[230],
													                DLG_TEXT_BASE[231] + GetFullName(pchar)+DLG_TEXT_BASE[232])),
												  NPCharRepPhrase(npchar,
												     DLG_TEXT_BASE[233]
													 +LinkRandPhrase(DLG_TEXT_BASE[234],DLG_TEXT_BASE[235],
													 pcharrepphrase(DLG_TEXT_BASE[236],DLG_TEXT_BASE[237])),
													 pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[238],DLG_TEXT_BASE[239])+RandPhraseSimple(DLG_TEXT_BASE[240],DLG_TEXT_BASE[241])
													 +RandPhraseSimple(DLG_TEXT_BASE[242],DLG_TEXT_BASE[243]),
													 DLG_TEXT_BASE[244] + GetFullName(pchar)+DLG_TEXT_BASE[245]
													 +RandPhraseSimple(DLG_TEXT_BASE[246], DLG_TEXT_BASE[247]))),
										"cycle", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase(DLG_TEXT_BASE[248],
													               DLG_TEXT_BASE[249]),
													pcharrepphrase(DLG_TEXT_BASE[250] +GetFullName(npchar)+DLG_TEXT_BASE[251],
													               DLG_TEXT_BASE[252] +GetAddress_FormToNPC(NPChar)+ ".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[253],
													               DLG_TEXT_BASE[254]),
												    pcharrepphrase(DLG_TEXT_BASE[255],
													               DLG_TEXT_BASE[256] +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[257],
													               DLG_TEXT_BASE[258] +GetFullName(npchar)+ DLG_TEXT_BASE[259]),
												    pcharrepphrase(DLG_TEXT_BASE[260],
													               DLG_TEXT_BASE[261])),
											  DLG_TEXT_BASE[262],
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase(DLG_TEXT_BASE[263],
													               DLG_TEXT_BASE[264]),
													pcharrepphrase(DLG_TEXT_BASE[265],
													               DLG_TEXT_BASE[266]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[267],
													               DLG_TEXT_BASE[268]),
													pcharrepphrase(DLG_TEXT_BASE[269],
													               DLG_TEXT_BASE[270] +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ DLG_TEXT_BASE[271])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[272],
													               DLG_TEXT_BASE[273]),
													pcharrepphrase(DLG_TEXT_BASE[274],
													               DLG_TEXT_BASE[275] + GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ DLG_TEXT_BASE[276])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[277],
													               DLG_TEXT_BASE[278]),
													pcharrepphrase(DLG_TEXT_BASE[279],
													               DLG_TEXT_BASE[280])),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase(DLG_TEXT_BASE[281],
													               DLG_TEXT_BASE[282]),
													pcharrepphrase(DLG_TEXT_BASE[283],
													               DLG_TEXT_BASE[284])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[285],
													               DLG_TEXT_BASE[286]),
												    pcharrepphrase(DLG_TEXT_BASE[287],
													               DLG_TEXT_BASE[288])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[289],
													               DLG_TEXT_BASE[290]),
													pcharrepphrase(DLG_TEXT_BASE[291],
													               DLG_TEXT_BASE[292])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[293],
													               DLG_TEXT_BASE[294]),
													pcharrepphrase(DLG_TEXT_BASE[295],
													               DLG_TEXT_BASE[296])),
											   npchar, Dialog.CurrentNode);
			link.l3.go = "quests";	
			if (pchar.questTemp.Ascold == "Seek_powder" && pchar.questTemp.Ascold.TraderId == npchar.id && !CheckAttribute(Pchar, "RomanticQuest.TalkInShop")) 
			{
				link.l3.go = "AscoldTrader";
			}
			if (CheckCharacterItem(pchar, "Powder_mummie") && pchar.questTemp.Ascold.TraderId == npchar.id) 
			{
				link.l3.go = "AscoldTrader_WasSeek";
			}		
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = DLG_TEXT_BASE[469] +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = link.l13 = DLG_TEXT_BASE[462]; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = link.l13 = DLG_TEXT_BASE[463]; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = link.l13 = DLG_TEXT_BASE[464]; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = DLG_TEXT_BASE[470]; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = DLG_TEXT_BASE[471];
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase(DLG_TEXT_BASE[297],
													               DLG_TEXT_BASE[298]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase(DLG_TEXT_BASE[299],
													               DLG_TEXT_BASE[300]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+DLG_TEXT_BASE[301])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[302],
													               DLG_TEXT_BASE[303]),
													pcharrepphrase(DLG_TEXT_BASE[304],
													               DLG_TEXT_BASE[305])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[306],
													               DLG_TEXT_BASE[307]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase(DLG_TEXT_BASE[308],
													               DLG_TEXT_BASE[309]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[310] +GetFullName(pchar)+ DLG_TEXT_BASE[311],
													               DLG_TEXT_BASE[312]),
													pcharrepphrase(DLG_TEXT_BASE[313],
													               DLG_TEXT_BASE[314] + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = DLG_TEXT_BASE[315];
				link.l1 = DLG_TEXT_BASE[316];
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[317], DLG_TEXT_BASE[318]);
			link.l1 = pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[319],
			                         DLG_TEXT_BASE[320],
									 DLG_TEXT_BASE[321]),
									 LinkRandPhrase(DLG_TEXT_BASE[322],
			                         DLG_TEXT_BASE[323],
									 DLG_TEXT_BASE[324]));
			link.l1.go = "trade_1";

			if(IsPCharHaveTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = DLG_TEXT_BASE[472];
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[328],
			                                          DLG_TEXT_BASE[329]),
									 RandPhraseSimple(DLG_TEXT_BASE[330],
									                  DLG_TEXT_BASE[331]));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = DLG_TEXT_BASE[473];
			link.l1 = DLG_TEXT_BASE[474];
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = DLG_TEXT_BASE[475]+DLG_TEXT_BASE[476];
			link.l1 = DLG_TEXT_BASE[477];
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = DLG_TEXT_BASE[478]+DLG_TEXT_BASE[479];
			link.l1 = DLG_TEXT_BASE[480];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = DLG_TEXT_BASE[481]+ GetSexPhrase("le capitaine, qui ramena","la lady, qui ramena") +DLG_TEXT_BASE[482];
				link.l1 = DLG_TEXT_BASE[483];
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, "+ GetSexPhrase("voici notre bienfaiteur","voici notre bienfaitrice") +DLG_TEXT_BASE[484];
				link.l1 = DLG_TEXT_BASE[485];
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = DLG_TEXT_BASE[486];
			link.l1 =  DLG_TEXT_BASE[487];
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = DLG_TEXT_BASE[488];
			link.l1 = DLG_TEXT_BASE[489];
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = DLG_TEXT_BASE[490];
			link.l1 = DLG_TEXT_BASE[491];
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[492],
					DLG_TEXT_BASE[493],
					"Oui, " + PChar.name + DLG_TEXT_BASE[494]);
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "Se sera " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99    = DLG_TEXT_BASE[495];
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase(DLG_TEXT_BASE[332],
					DLG_TEXT_BASE[333]),
					pcharrepphrase(DLG_TEXT_BASE[334] +GetFullName(pchar)+ DLG_TEXT_BASE[335],
					DLG_TEXT_BASE[336]));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[337],
					DLG_TEXT_BASE[338] +GetFullName(npchar)+ DLG_TEXT_BASE[339]),
					pcharrepphrase(DLG_TEXT_BASE[340],
					DLG_TEXT_BASE[341]));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[496],
				DLG_TEXT_BASE[497],
				PChar.name + DLG_TEXT_BASE[498]);
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "Se sera " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99    = DLG_TEXT_BASE[495];
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[499], 
						DLG_TEXT_BASE[500],
						DLG_TEXT_BASE[501]);
					link.l1 = DLG_TEXT_BASE[502];
					link.l1.go = "exit";
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[503], 
						DLG_TEXT_BASE[504],
						DLG_TEXT_BASE[505]);
					link.l1 = DLG_TEXT_BASE[506];
					link.l1.go = "exit";
					link.l2 = DLG_TEXT_BASE[507];
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[508], 
					DLG_TEXT_BASE[509],
					DLG_TEXT_BASE[510]);
				link.l1 = DLG_TEXT_BASE[511];
				link.l1.go = "TransferGoods_2";
				link.l2 = DLG_TEXT_BASE[512];
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase(DLG_TEXT_BASE[332],
					DLG_TEXT_BASE[333]),
					pcharrepphrase(DLG_TEXT_BASE[334] +GetFullName(pchar)+ DLG_TEXT_BASE[335],
					DLG_TEXT_BASE[336]));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[337],
					DLG_TEXT_BASE[338] +GetFullName(npchar)+ DLG_TEXT_BASE[339]),
					pcharrepphrase(DLG_TEXT_BASE[340],
					DLG_TEXT_BASE[341]));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = DLG_TEXT_BASE[513] + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = DLG_TEXT_BASE[514];
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[515];
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Venez.";
				link.l1 = "Merci.";
				link.l1.go = "storage_2";
			}
			link.l2 = DLG_TEXT_BASE[516];
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = DLG_TEXT_BASE[517] + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + DLG_TEXT_BASE[518]+
				DLG_TEXT_BASE[519];	
			link.l1 = DLG_TEXT_BASE[520];
			link.l1.go = "storage_1";
			link.l2 = DLG_TEXT_BASE[521];
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = DLG_TEXT_BASE[522];
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = DLG_TEXT_BASE[523];
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[524];
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = DLG_TEXT_BASE[525];
			link.l1 = DLG_TEXT_BASE[527];
			link.l1.go = "storage_4";
			link.l2 = DLG_TEXT_BASE[526];
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = DLG_TEXT_BASE[513] + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Bien.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[528];
				link.l1 = "Bein.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
			if (pchar.questTemp.BlueBird == "begin" && sti(npchar.nation) == GetBaseHeroNation() && sti(npchar.nation) != PIRATE && npchar.city != "Panama")
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[342], DLG_TEXT_BASE[343]);
				link.l1 = DLG_TEXT_BASE[344]; 
				link.l1.go = "RBlueBird";
				break;
			}	
//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 6 && drand(2) == 0) 
			{
				dialog.text = DLG_TEXT_BASE[529];
				link.l1 = DLG_TEXT_BASE[530]; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = DLG_TEXT_BASE[531]+pchar.questTemp.Shadowtrader.Guardername+DLG_TEXT_BASE[532];
					link.l1 = DLG_TEXT_BASE[533]; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = DLG_TEXT_BASE[534];
					link.l1 = DLG_TEXT_BASE[535]; 
					link.l1.go = "Shadowtrader_trouble";
				pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && GetQuestPastDayParam("pchar.questTemp.Shadowtrader.EndFort") > 0)
				{
					dialog.text = DLG_TEXT_BASE[536]+DLG_TEXT_BASE[537];
					link.l1 = DLG_TEXT_BASE[538]; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Alors, quelles sont les nouvelles " + pchar.name + "?";
					link.l1 = DLG_TEXT_BASE[539]; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = DLG_TEXT_BASE[540] + pchar.name + DLG_TEXT_BASE[541]+DLG_TEXT_BASE[542];
					link.l1 = DLG_TEXT_BASE[543]; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = DLG_TEXT_BASE[544] + pchar.name + DLG_TEXT_BASE[545]+DLG_TEXT_BASE[546];
					link.l1 = DLG_TEXT_BASE[547]; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
	
			//Jason --> генератор Сомнительное предложение
			/*if (drand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "Oh! You're just in time, captain. I would like to ask you to do me a favor.";
					link.l1 = "Let's listen."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "I'm all ears, captain.";
				link.l5 = "I have brought your order."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "Oh! You're just in time, captain. I require a special favor.";
				link.l5 = "Let's listen."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "I'm all ears, captain.";
				link.l5 = "I have brought you the slaves."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = DLG_TEXT_BASE[548]+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && drand(4) == 4) 
			{
				dialog.text = DLG_TEXT_BASE[549];
				link.l1 = DLG_TEXT_BASE[550]; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = DLG_TEXT_BASE[551]+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Heh! Oui c'est certain. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" et le cargo - " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+ ", n'est plus en la pocession de votre rival."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = DLG_TEXT_BASE[552];
				link.l1 = DLG_TEXT_BASE[553] + npchar.name + DLG_TEXT_BASE[554]; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = DLG_TEXT_BASE[345] + GetFullName(&Characters[iTmp]) + DLG_TEXT_BASE[346];
				link.l1 = DLG_TEXT_BASE[347];
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,DLG_TEXT_BASE[348],DLG_TEXT_BASE[349]);
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[350], DLG_TEXT_BASE[351]);
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = DLG_TEXT_BASE[352];
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple(DLG_TEXT_BASE[353],
								                           DLG_TEXT_BASE[354]);
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = DLG_TEXT_BASE[355] +GetAddress_FormToNPC(NPChar)+ DLG_TEXT_BASE[356];
    				link.l1.go = "generate_quest";
    			}
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[357],
	                                                          DLG_TEXT_BASE[358]),
	                                        RandPhraseSimple(DLG_TEXT_BASE[359],
	                                                         DLG_TEXT_BASE[360]));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple(DLG_TEXT_BASE[361] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[362]);
					link.l4.go = "IntelligenceForAll";
				}	
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[367],DLG_TEXT_BASE[368]),RandPhraseSimple(DLG_TEXT_BASE[369],DLG_TEXT_BASE[370]));,
    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = DLG_TEXT_BASE[555];
						link.l7.go = "storage_0";
						link.l8 = DLG_TEXT_BASE[556];
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = DLG_TEXT_BASE[557];
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = DLG_TEXT_BASE[558]+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[559];
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				if (pchar.questTemp.BlueBird == "weWon" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l9 = DLG_TEXT_BASE[363];
					link.l9.go = "RBlueBirdWon";
				}
				if (pchar.questTemp.BlueBird == "DieHard" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l9 = DLG_TEXT_BASE[364];
					link.l9.go = "RBlueBirdDieHard";
				}
				if (pchar.questTemp.BlueBird == "returnMoney" && pchar.questTemp.BlueBird.traiderId == npchar.id && sti(pchar.questTemp.BlueBird.count) > 0)
				{
					if (sti(pchar.questTemp.BlueBird.count) < 1)
					{
						link.l9 = DLG_TEXT_BASE[365];
						link.l9.go = "RBlueBird_retMoney_1";
					}
					else
					{
						link.l9 = DLG_TEXT_BASE[366];
						link.l9.go = "RBlueBird_retMoney_3";
					}
				}				
				// <-- homo
				link.l99 = DLG_TEXT_BASE[371];
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[372], DLG_TEXT_BASE[373] +GetFullName(npchar)+ DLG_TEXT_BASE[374]), pcharrepphrase(DLG_TEXT_BASE[375], DLG_TEXT_BASE[376]));
                link.l1.go = "exit";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[377],
	                                                          DLG_TEXT_BASE[378]),
	                                        RandPhraseSimple(DLG_TEXT_BASE[379],
	                                                         DLG_TEXT_BASE[380]));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple(DLG_TEXT_BASE[381] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[382]);
					link.l7.go = "IntelligenceForAll";
				}	
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = DLG_TEXT_BASE[383] + NationNameAblative(sti(NPChar.nation)) + ".";
					link.l1 = DLG_TEXT_BASE[384];
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear() + DLG_TEXT_BASE[385] + GetFullName(pchar)+ DLG_TEXT_BASE[386] +
                                      RandPhraseSimple(DLG_TEXT_BASE[387],DLG_TEXT_BASE[388]) + DLG_TEXT_BASE[389];
						link.l1 = RandPhraseSimple(DLG_TEXT_BASE[390],
						                           RandSwear()+ DLG_TEXT_BASE[391]+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar, DLG_TEXT_BASE[392]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[393],DLG_TEXT_BASE[394]);
						link.l1 = DLG_TEXT_BASE[395];
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar, DLG_TEXT_BASE[396],DLG_TEXT_BASE[397]+GetFullName(pchar)+DLG_TEXT_BASE[398]);
    							link.l1 = NPCharRepPhrase(npchar, DLG_TEXT_BASE[399],DLG_TEXT_BASE[400]);
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = DLG_TEXT_BASE[560] + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
                                }
                                dialog.text = DLG_TEXT_BASE[401] +
                                               GetGoodsNameAlt(iTradeGoods)+ DLG_TEXT_BASE[402] + FindRussianQtyString(iQuantityGoods) + DLG_TEXT_BASE[403] +
                                           sNation + sTemp + DLG_TEXT_BASE[561] +  FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)) +
                                           DLG_TEXT_BASE[404] +
                                           FindRussianMoneyString(iMoney) + DLG_TEXT_BASE[405];
    							link.l1 = DLG_TEXT_BASE[406];
    							link.l1.go = "exit_trade";
    							link.l2  = DLG_TEXT_BASE[407];
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = DLG_TEXT_BASE[408]+
                                          XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + DLG_TEXT_BASE[409];
    						link.l1 = DLG_TEXT_BASE[410];
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, DLG_TEXT_BASE[411],DLG_TEXT_BASE[412]);
				link.l1 = NPCharRepPhrase(npchar, DLG_TEXT_BASE[413], DLG_TEXT_BASE[414]);
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear() + DLG_TEXT_BASE[415];
				link.l1 = DLG_TEXT_BASE[416];
				link.l1.go = "generate_quest_failed";
				link.l9 = DLG_TEXT_BASE[417];
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = DLG_TEXT_BASE[418] +
                GetGoodsNameAlt(iTradeGoods) + DLG_TEXT_BASE[419] + FindRussianQtyString(iQuantityGoods) + DLG_TEXT_BASE[420] +
                FindRussianMoneyString(sti(pchar.CargoQuest.iMoney)) + ".";
				link.l1 = DLG_TEXT_BASE[421];
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear() + DLG_TEXT_BASE[422]+GetAddress_Form(NPChar)+
                              DLG_TEXT_BASE[423] + RandPhraseSimple(DLG_TEXT_BASE[424],DLG_TEXT_BASE[425])+
                              DLG_TEXT_BASE[426];
				link.l1 = RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[427],
                                                         DLG_TEXT_BASE[428]);
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = DLG_TEXT_BASE[429]
                              + FindRussianQtyString(iTmp) + DLG_TEXT_BASE[430];
				link.l9 = RandPhraseSimple(DLG_TEXT_BASE[431],
                                           RandSwear() +DLG_TEXT_BASE[432]);
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[433]+GetFullName(pchar)+".";
				link.l1 = DLG_TEXT_BASE[434];
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = DLG_TEXT_BASE[435] + FindRussianMoneyString(iMoney) + DLG_TEXT_BASE[436];
			link.l1 = DLG_TEXT_BASE[437];
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Voici le montant requis.";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = DLG_TEXT_BASE[439];
			link.l1 = DLG_TEXT_BASE[440];
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = DLG_TEXT_BASE[441] +
            LanguageConvertString(iSeaGoods, "seg_" + Goods[iTradeGoods].Name)+ " vers " + XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony) + ".";
			link.l1 = DLG_TEXT_BASE[442];
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear() + GetAddress_Form(NPChar) +DLG_TEXT_BASE[443];
			link.l1 = DLG_TEXT_BASE[444];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[445];
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = DLG_TEXT_BASE[446]
                              + FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)) + DLG_TEXT_BASE[447];
				link.l9 = RandPhraseSimple(DLG_TEXT_BASE[448],
                                           RandSwear() +DLG_TEXT_BASE[449]);
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[450];
    			link.l1 = DLG_TEXT_BASE[451];
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;

		//Jason --> -------------------мини-квест Бесчестный конкурент-------------------------------------------
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = DLG_TEXT_BASE[562]+pchar.questTemp.Shadowtrader.Guardername+DLG_TEXT_BASE[563];
			link.l1 = DLG_TEXT_BASE[564];
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = DLG_TEXT_BASE[565];
			link.l2.go = "exit";
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = DLG_TEXT_BASE[566];
			link.l1 = DLG_TEXT_BASE[567];
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = DLG_TEXT_BASE[568];
			link.l1 = DLG_TEXT_BASE[569];
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = DLG_TEXT_BASE[570];
			link.l2.go = "Shadowtrader_fort_end";
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = DLG_TEXT_BASE[571];
			link.l1 = DLG_TEXT_BASE[572];
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = DLG_TEXT_BASE[573];
			link.l1 = DLG_TEXT_BASE[574];
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = DLG_TEXT_BASE[575];
			link.l1 = DLG_TEXT_BASE[576] + npchar.name + DLG_TEXT_BASE[577];
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = DLG_TEXT_BASE[578];
			link.l1 = "Contrebandiers ?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = DLG_TEXT_BASE[579]+DLG_TEXT_BASE[580];
			link.l1 = DLG_TEXT_BASE[581];
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = DLG_TEXT_BASE[582]+DLG_TEXT_BASE[583];
			link.l1 = DLG_TEXT_BASE[584];
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = DLG_TEXT_BASE[585]+pchar.questTemp.Shadowtrader.Guardername+DLG_TEXT_BASE[586];
			link.l1 = DLG_TEXT_BASE[587];
			link.l1.go = "Shadowtrader_end";
			link.l2 = DLG_TEXT_BASE[588];
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = DLG_TEXT_BASE[589];
			link.l1 = DLG_TEXT_BASE[590];
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = DLG_TEXT_BASE[591];
			link.l1 = DLG_TEXT_BASE[592];
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = DLG_TEXT_BASE[593];
			link.l1 = DLG_TEXT_BASE[594];
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = DLG_TEXT_BASE[595];
			link.l1 = DLG_TEXT_BASE[596] + npchar.name + "!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			CloseQuestHeader("Shadowtrader");
		break;
	// <-- мини-квест Бесчестный конкурент
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = DLG_TEXT_BASE[597];
			link.l1 = DLG_TEXT_BASE[598];
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = DLG_TEXT_BASE[599];
			link.l1 = DLG_TEXT_BASE[600];
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[601];
			link.l1 = DLG_TEXT_BASE[602];
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
		break;
		
		case "Wine_Price":
			dialog.text = DLG_TEXT_BASE[603];
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = DLG_TEXT_BASE[604];
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = DLG_TEXT_BASE[605];
				link.l1 = DLG_TEXT_BASE[606];
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = DLG_TEXT_BASE[607];
				link.l1 = DLG_TEXT_BASE[608];
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+DLG_TEXT_BASE[609] + FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = DLG_TEXT_BASE[610];
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = DLG_TEXT_BASE[611];
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = DLG_TEXT_BASE[612];
			link.l1 = DLG_TEXT_BASE[613];
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = DLG_TEXT_BASE[614];
			link.l1 = DLG_TEXT_BASE[615];
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info (DLG_TEXT_BASE[616]);
			AddQuestRecord("Wine", "8");
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(7-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+drand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = DLG_TEXT_BASE[617] + GetGoodsNameAlt(iCGood)+ DLG_TEXT_BASE[618]+DLG_TEXT_BASE[619] + FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)) + DLG_TEXT_BASE[620] + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price)) + DLG_TEXT_BASE[621] + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + DLG_TEXT_BASE[622]+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+DLG_TEXT_BASE[623];
			link.l1 = DLG_TEXT_BASE[19];
			link.l1.go = "Contraoffer_1";
			link.l2 = DLG_TEXT_BASE[624];
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = DLG_TEXT_BASE[625];
			link.l1 = DLG_TEXT_BASE[626];
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = DLG_TEXT_BASE[627];
				link.l1 = DLG_TEXT_BASE[628];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[629] + GetGoodsNameAlt(iCGood)+ DLG_TEXT_BASE[630] + FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty) + DLG_TEXT_BASE[631];
				link.l1 = DLG_TEXT_BASE[632] + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = DLG_TEXT_BASE[633] + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ".";
		link.l1 = DLG_TEXT_BASE[634];
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = DLG_TEXT_BASE[635];
				link.l1 = DLG_TEXT_BASE[636];
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = DLG_TEXT_BASE[637]+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+DLG_TEXT_BASE[638]+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+DLG_TEXT_BASE[639]+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+DLG_TEXT_BASE[640]+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = DLG_TEXT_BASE[21];
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = DLG_TEXT_BASE[641];
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = DLG_TEXT_BASE[642];
			link.l1 = DLG_TEXT_BASE[643];
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = DLG_TEXT_BASE[644];
				link.l1 = DLG_TEXT_BASE[645];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[646] + FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty) + DLG_TEXT_BASE[647];
				link.l1 = DLG_TEXT_BASE[648] + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = DLG_TEXT_BASE[649] + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)) + DLG_TEXT_BASE[650];
			link.l1 = DLG_TEXT_BASE[651];
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+DLG_TEXT_BASE[652];
			link.l1 = DLG_TEXT_BASE[653]+pchar.GenQuest.Device.Shipyarder.Describe+DLG_TEXT_BASE[654];
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = DLG_TEXT_BASE[655];
				link.l1 = DLG_TEXT_BASE[656];
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[657];
				link.l1 = DLG_TEXT_BASE[658];
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = DLG_TEXT_BASE[659]+DLG_TEXT_BASE[660];
			link.l1 = DLG_TEXT_BASE[661];
			link.l1.go = "Sunplace_1";
			link.l2 = DLG_TEXT_BASE[662];
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + drand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = DLG_TEXT_BASE[663]+pchar.GenQuest.Sunplace.Trader.Enemyname+DLG_TEXT_BASE[664]+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+DLG_TEXT_BASE[665] + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+ DLG_TEXT_BASE[666];
			link.l1 = DLG_TEXT_BASE[667];
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = DLG_TEXT_BASE[668]+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Abl")+DLG_TEXT_BASE[669]+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+DLG_TEXT_BASE[670] + XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen") + DLG_TEXT_BASE[671]+pchar.GenQuest.Sunplace.Trader.Enemyname +DLG_TEXT_BASE[672] + FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))".";
			link.l1 = DLG_TEXT_BASE[673];
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = DLG_TEXT_BASE[674];
			link.l1 = DLG_TEXT_BASE[675] + npchar.name + "!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Pauvre "+pchar.GenQuest.Sunplace.Trader.Enemyname+DLG_TEXT_BASE[676];
			link.l1 = DLG_TEXT_BASE[677];
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = DLG_TEXT_BASE[678];
			link.l1 = "He, " + npchar.name + DLG_TEXT_BASE[679];
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_BASE[680], DLG_TEXT_BASE[681], DLG_TEXT_BASE[682], DLG_TEXT_BASE[683], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[684], DLG_TEXT_BASE[685], DLG_TEXT_BASE[686], DLG_TEXT_BASE[687], npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[688], DLG_TEXT_BASE[689], DLG_TEXT_BASE[690], DLG_TEXT_BASE[691], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[692], DLG_TEXT_BASE[693], DLG_TEXT_BASE[694], DLG_TEXT_BASE[695], npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		case "trial":
			dialog.text = DLG_TEXT_BASE[696];
			link.l1 = DLG_TEXT_BASE[697];
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = DLG_TEXT_BASE[698];
			link.l1 = DLG_TEXT_BASE[699];
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			TakeNItems(pchar, "gold_dublon", 400);
			Log_Info(DLG_TEXT_BASE[17]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[700];
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			CloseQuestHeader("Trial");
		break;
		
		/*case "trial":
			dialog.text = "God, what are you so rasshumelis, young man! Be restrained in the end, and expressions when talking about respectable people! Gerard LeCroes departed from Guadeloupe in the expedition to the mainland, but for you he left a message\nYou calm down, sir? Ready to listen to me?";
			link.l1 = "Hm... Please excuse me, monsieur. I got heated up a bit. I am listening.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Very good. Next time try to ask first, and then crying out loud. Alright... Do you know a man by the name Simon Maurois?";
			link.l1 = "Ha! Everyone has heard of Simon Maurois! Or course I know him.";
			link.l1.go = "trial_2";
			link.l2 = "Never heard about him. Who is he?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Excellent. Go to him, then. It was him who financed the expedition of monsieur Shoke, so you can collect your reward from him. So, was it really necessary to get so steamed up?";
			link.l1 = "Once again, I beg for your pardon... Thanks for your help, monsieur. I will see monsieur Maurois at once!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "He is the owner of Maurois banking house and the head of the branch in Capsterville. So you'll have to go to Saint-Christopher and visit the bank of Capsterville. It was monsieur Maurois who financed the expedition of monsieur Shoke, so you can collect your reward from him. So, was it really necessary to get so steamed up?";
			link.l1 = "Once again, I beg for your pardon... Thanks for your help, monsieur. I will see monsieur Maurois at once!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		case "no_quests":
			dialog.text = DLG_TEXT_BASE[452];
			link.l1 = DLG_TEXT_BASE[453];
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":	
			if (rand(20) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "questTemp.Ascold"))//eddy. Аскольд, начало
			{
				dialog.Text = DLG_TEXT_BASE[454];
				Link.l1 = DLG_TEXT_BASE[455];
				Link.l1.go = "exit";
				SaveCurrentQuestDateParam("questTemp.Ascold");
				pchar.questTemp.Ascold = "Seek_powder";
				pchar.questTemp.Ascold.TraderId = npchar.city + "_trader";
				AddQuestRecord("Ascold", "1");
				AddQuestUserData("Ascold", "sName", GetFullName(npchar));
				AddQuestUserData("Ascold", "sCity", XI_ConvertString("Colony" + npchar.city + "Dat"));
			}
			else
			{			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();	
			}
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}