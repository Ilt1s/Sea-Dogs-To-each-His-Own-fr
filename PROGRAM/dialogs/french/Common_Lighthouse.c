#include "SD\TEXT\DIALOGS\Common_lighthouse.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3]+ GetSexPhrase("canaille","rascal") +DLG_TEXT_BASE[4]+ GetSexPhrase("sale pirate","salope") +" !", ""+ GetSexPhrase("sale","sale") +DLG_TEXT_BASE[5], DLG_TEXT_BASE[6]+ GetSexPhrase("sale type","salope") +DLG_TEXT_BASE[7]));
				link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9] + XI_ConvertString("Colony" + npchar.city + "Gen") + " !"), 
					RandPhraseSimple("Allez au diable !", DLG_TEXT_BASE[10]));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[11]+GetFullName(npchar)+DLG_TEXT_BASE[12], DLG_TEXT_BASE[13]+GetFullName(npchar)+DLG_TEXT_BASE[14]);
				link.l1 = "Salutation, "+npchar.name+" ! On me nomme "+GetFullName(pchar)+DLG_TEXT_BASE[15];
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[16]+GetFullName(pchar)+DLG_TEXT_BASE[17];
				link.l1 = DLG_TEXT_BASE[18];
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = DLG_TEXT_BASE[19];
			link.l1 = DLG_TEXT_BASE[20];
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = DLG_TEXT_BASE[21];
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[22],DLG_TEXT_BASE[23]);
			link.l1.go = "rumours_lighthouse";
			link.l2 = DLG_TEXT_BASE[24];
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "Alors, "+npchar.name+DLG_TEXT_BASE[25];
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+DLG_TEXT_BASE[26];
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Ecoutez, "+npchar.name+DLG_TEXT_BASE[27];
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = DLG_TEXT_BASE[28];
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = DLG_TEXT_BASE[29];
			link.l4.go = "quests";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = DLG_TEXT_BASE[30]+DLG_TEXT_BASE[31]+DLG_TEXT_BASE[32]+DLG_TEXT_BASE[33];
			link.l1 = "Ecoutez, "+npchar.name+DLG_TEXT_BASE[34];
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары
			npchar.quest.goods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 100+drand(200);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 50+drand(100);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (drand(2) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = DLG_TEXT_BASE[35] + GetGoodsNameAlt(sti(npchar.quest.goods))+ DLG_TEXT_BASE[36] + FindRussianQtyString(sti(npchar.quest.goodsqty)) + DLG_TEXT_BASE[37]+FindRussianMoneyString(sti(npchar.quest.goodsprice))+DLG_TEXT_BASE[38];
				link.l1 = DLG_TEXT_BASE[39];
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = DLG_TEXT_BASE[40]+FindRussianMoneyString(sti(npchar.quest.goodscost))+DLG_TEXT_BASE[41];
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = DLG_TEXT_BASE[42];
			link.l1 = DLG_TEXT_BASE[43];
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact"))
			{
				dialog.text = DLG_TEXT_BASE[44];
				link.l1 = DLG_TEXT_BASE[45];
				link.l1.go = "Trade_artefact_1";
				link.l2 = DLG_TEXT_BASE[46];
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[47];
				link.l1 = DLG_TEXT_BASE[48];
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = DLG_TEXT_BASE[49];
			else dialog.text = DLG_TEXT_BASE[50];
			link.l1 = DLG_TEXT_BASE[51];
			link.l1.go = "Trade_lighthouse";
			link.l2 = DLG_TEXT_BASE[52];
			link.l2.go = "rumours_lighthouse";
			link.l3 = DLG_TEXT_BASE[53];
			link.l3.go = "quests";
			link.l4 = DLG_TEXT_BASE[54]+npchar.name+DLG_TEXT_BASE[55];
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = DLG_TEXT_BASE[56];
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = DLG_TEXT_BASE[57];
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = DLG_TEXT_BASE[58];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = DLG_TEXT_BASE[60];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = DLG_TEXT_BASE[61];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = DLG_TEXT_BASE[62];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = DLG_TEXT_BASE[63];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = DLG_TEXT_BASE[65];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = DLG_TEXT_BASE[66];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = DLG_TEXT_BASE[67];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = DLG_TEXT_BASE[68];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = DLG_TEXT_BASE[69];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = DLG_TEXT_BASE[71];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = DLG_TEXT_BASE[73];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = DLG_TEXT_BASE[75];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = DLG_TEXT_BASE[76];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = DLG_TEXT_BASE[77];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = DLG_TEXT_BASE[78];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = DLG_TEXT_BASE[79];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = DLG_TEXT_BASE[80];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = DLG_TEXT_BASE[81];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = DLG_TEXT_BASE[82];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = DLG_TEXT_BASE[83];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = DLG_TEXT_BASE[84];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = DLG_TEXT_BASE[85];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = DLG_TEXT_BASE[86];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = DLG_TEXT_BASE[87];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = DLG_TEXT_BASE[88];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = DLG_TEXT_BASE[89];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = DLG_TEXT_BASE[90];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = DLG_TEXT_BASE[91];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = DLG_TEXT_BASE[92];
			link.l1 = DLG_TEXT_BASE[93]+npchar.name+" !";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = DLG_TEXT_BASE[94];
				if(sti(pchar.money) >= 15000)
				{
					link.l1 = DLG_TEXT_BASE[95];
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[96];
					link.l1.go = "exit";
				}
			}
			else
			{
			dialog.text = DLG_TEXT_BASE[97];
			link.l1 = "Bien.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			AddMoneyToCharacter(pchar, -15000);
			AddMoneyToCharacter(npchar, 15000);
			dialog.text = DLG_TEXT_BASE[98];
			link.l1 = "Merci, "+npchar.name+" !";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info(DLG_TEXT_BASE[99]+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[100];
			link.l1 = DLG_TEXT_BASE[101];
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = DLG_TEXT_BASE[102]+DLG_TEXT_BASE[103];
				link.l1 = "Certainement !";
				link.l1.go = "caleuche_2";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[104];
				link.l1 = DLG_TEXT_BASE[105];
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = DLG_TEXT_BASE[106];
			link.l1 = DLG_TEXT_BASE[107];
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = DLG_TEXT_BASE[108]+DLG_TEXT_BASE[109];
			link.l1 = "Je vois...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = DLG_TEXT_BASE[110];
			link.l1 = DLG_TEXT_BASE[111];
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = DLG_TEXT_BASE[112];
			link.l1 = DLG_TEXT_BASE[113];
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = DLG_TEXT_BASE[114];
			link.l1 = DLG_TEXT_BASE[115];
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = DLG_TEXT_BASE[116];
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = DLG_TEXT_BASE[117];
			link.l1 = DLG_TEXT_BASE[118];
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = DLG_TEXT_BASE[119];
			link.l1 = DLG_TEXT_BASE[120];
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = DLG_TEXT_BASE[121];
			link.l1 = DLG_TEXT_BASE[122];
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = DLG_TEXT_BASE[123];
			link.l1 = DLG_TEXT_BASE[124];
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = DLG_TEXT_BASE[125];
			link.l1 = DLG_TEXT_BASE[126];
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Voici un"+ GetSexPhrase(DLG_TEXT_BASE[127],DLG_TEXT_BASE[128]) +" !!!", DLG_TEXT_BASE[129], DLG_TEXT_BASE[130]);
			link.l1 = DLG_TEXT_BASE[131];
			link.l1.go = "fight";
		break;
	}
}