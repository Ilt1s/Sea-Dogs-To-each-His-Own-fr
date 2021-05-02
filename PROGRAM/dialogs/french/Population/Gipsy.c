#include "SD\TEXT\DIALOGS\Common_population.h"
// ugeen <-- добавил продажу мышьяка из под полы
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_BASE[48];
			link.l1 = DLG_TEXT_BASE[49];
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple(DLG_TEXT_BASE[50], DLG_TEXT_BASE[51]);
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[52],DLG_TEXT_BASE[53],DLG_TEXT_BASE[54]);
				link.l1 = DLG_TEXT_BASE[55];
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = DLG_TEXT_BASE[56];
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = DLG_TEXT_BASE[57];
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = DLG_TEXT_BASE[58];
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple(DLG_TEXT_BASE[59],DLG_TEXT_BASE[60]);
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = DLG_TEXT_BASE[61];
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = DLG_TEXT_BASE[62];
			link.l1 = DLG_TEXT_BASE[63];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[64];
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = DLG_TEXT_BASE[65];
			link.l1 = "100 pesos";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 pesos";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 pesos";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 pesos";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = DLG_TEXT_BASE[66]+sTemp+"";
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[67],DLG_TEXT_BASE[68],DLG_TEXT_BASE[69]);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[70];
				link.l1 = DLG_TEXT_BASE[71];
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = DLG_TEXT_BASE[72]+sTemp+"";
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[73],DLG_TEXT_BASE[74],DLG_TEXT_BASE[75]);
				link.l1.go = "exit";
				if (drand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[76];
				link.l1 = DLG_TEXT_BASE[77];
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = DLG_TEXT_BASE[78]+sTemp+"";
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[79],DLG_TEXT_BASE[80],DLG_TEXT_BASE[81]);
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (drand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[82];
				link.l1 = DLG_TEXT_BASE[83];
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = DLG_TEXT_BASE[84]+sTemp+"";
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[85],DLG_TEXT_BASE[86],DLG_TEXT_BASE[87]);
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[88];
				link.l1 = DLG_TEXT_BASE[89];
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (drand(3) + 1) * 10;
			if(drand(10) == 3)
			{				
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[90],DLG_TEXT_BASE[91],DLG_TEXT_BASE[92]);
				link.l1 = DLG_TEXT_BASE[93];
				link.l1.go = "get_poison_2";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[94];
				link.l1 = DLG_TEXT_BASE[95];
				link.l1.go = "exit";
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = DLG_TEXT_BASE[96]+sti(npchar.quest.poison_price)+" doublons.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.poison_price)) 
			{				
				link.l1 = DLG_TEXT_BASE[97];
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[98];
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = DLG_TEXT_BASE[99];
			link.l1 = DLG_TEXT_BASE[100];
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[101],DLG_TEXT_BASE[102],DLG_TEXT_BASE[103]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[104],DLG_TEXT_BASE[105],DLG_TEXT_BASE[106]);
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = DLG_TEXT_BASE[107];
			link.l1 = DLG_TEXT_BASE[108];
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+drand(25)+drand(30))
			{
				dialog.text = DLG_TEXT_BASE[109];
				link.l1 = DLG_TEXT_BASE[110];
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[111],DLG_TEXT_BASE[112],DLG_TEXT_BASE[113])+DLG_TEXT_BASE[114];
				link.l1 = DLG_TEXT_BASE[115];
				link.l1.go = "mangarosa_trade";
				link.l2 = DLG_TEXT_BASE[116];
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[117];
			link.l1 = DLG_TEXT_BASE[118];
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[119],DLG_TEXT_BASE[120],DLG_TEXT_BASE[121]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[122],DLG_TEXT_BASE[123],DLG_TEXT_BASE[124]);
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = DLG_TEXT_BASE[125];
			link.l1 = DLG_TEXT_BASE[126];
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = DLG_TEXT_BASE[127];
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[128];
			link.l1 = DLG_TEXT_BASE[129];
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = DLG_TEXT_BASE[130];
			link.l1 = DLG_TEXT_BASE[131];
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = DLG_TEXT_BASE[132];
			link.l1 = DLG_TEXT_BASE[133];
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = DLG_TEXT_BASE[134]+DLG_TEXT_BASE[646];
			link.l1 = DLG_TEXT_BASE[135];
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[136];
			link.l1 = DLG_TEXT_BASE[137];
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = DLG_TEXT_BASE[138];
			link.l1 = DLG_TEXT_BASE[139];
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = DLG_TEXT_BASE[140];
			link.l1 = DLG_TEXT_BASE[141];
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[142], DLG_TEXT_BASE[143]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[144],DLG_TEXT_BASE[145],DLG_TEXT_BASE[146]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (drand(19))
	{
		case 0: sText = DLG_TEXT_BASE[147] break;
		case 1: sText = DLG_TEXT_BASE[148] break;
		case 2: sText = DLG_TEXT_BASE[149] break;
		case 3: sText = DLG_TEXT_BASE[150] break;
		case 4: sText = DLG_TEXT_BASE[151] break;
		case 5: sText = DLG_TEXT_BASE[152] break;
		case 6: sText = DLG_TEXT_BASE[153] break;
		case 7: sText = DLG_TEXT_BASE[154] break;
		case 8: sText = DLG_TEXT_BASE[155] break;
		case 9: sText = DLG_TEXT_BASE[156] break;
		case 10: sText = DLG_TEXT_BASE[157] break;
		case 11: sText = DLG_TEXT_BASE[158] break;
		case 12: sText = DLG_TEXT_BASE[159] break;
		case 13: sText = DLG_TEXT_BASE[160] break;
		case 14: sText = DLG_TEXT_BASE[161] break;
		case 15: sText = DLG_TEXT_BASE[162] break;
		case 16: sText = DLG_TEXT_BASE[163] break;
		case 17: sText = DLG_TEXT_BASE[164] break;
		case 18: sText = DLG_TEXT_BASE[165] break;
		case 19: sText = DLG_TEXT_BASE[166] break;
	}
	return sText;
}
