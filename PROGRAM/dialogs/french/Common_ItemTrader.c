#include "SD\DIALOGS\russian\Rumours\Common_rumours.c" //Jason
#include "SD\TEXT\DIALOGS\Common_ItemTrader.h"
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			dialog.text = NPCharSexPhrase(npchar, DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]);
			link.l1 = DLG_TEXT_BASE[8];
			link.l1.go = "Trade_exit";
			
   			link.l2 = DLG_TEXT_BASE[9];
			link.l2.go = "quests";
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = DLG_TEXT_BASE[75];
				link.l4.go = "mangarosa";
			}
			link.l3 = DLG_TEXT_BASE[13];
			link.l3.go = "exit";

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = DLG_TEXT_BASE[76];
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = DLG_TEXT_BASE[77];
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = DLG_TEXT_BASE[78];
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = DLG_TEXT_BASE[79]+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			if (pchar.questTemp.Ascold == "Seek_powder")
			{
   				link.l6 = LinkRandPhrase(DLG_TEXT_BASE[10], DLG_TEXT_BASE[11], DLG_TEXT_BASE[12]);
				link.l6.go = "AscoldMerchant";
			}			
			//<-- генератор Неудачливый вор

			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = DLG_TEXT_BASE[80];
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = DLG_TEXT_BASE[81];
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = DLG_TEXT_BASE[82];
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = DLG_TEXT_BASE[83];
			link.l1 = DLG_TEXT_BASE[84];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
		break;
		
		case "Wine_Bottles":
			dialog.text = DLG_TEXT_BASE[85];
			link.l1 = DLG_TEXT_BASE[86];
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = DLG_TEXT_BASE[87];
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = DLG_TEXT_BASE[88];
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = DLG_TEXT_BASE[89];
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = DLG_TEXT_BASE[90]+pchar.questTemp.Wine.Name+DLG_TEXT_BASE[91];
			link.l1 = DLG_TEXT_BASE[92];
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = DLG_TEXT_BASE[93];
			link.l1 = DLG_TEXT_BASE[94];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = DLG_TEXT_BASE[95];
			link.l1 = DLG_TEXT_BASE[96]+pchar.questTemp.Wine.Name+DLG_TEXT_BASE[97];
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = DLG_TEXT_BASE[98]+pchar.questTemp.Wine.Name+DLG_TEXT_BASE[99];
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = DLG_TEXT_BASE[100];
			link.l1 = DLG_TEXT_BASE[101];
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = DLG_TEXT_BASE[102];
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = DLG_TEXT_BASE[103];
				link.l1.go = "Wine_Bottles_3";
			}
			link.l2 = DLG_TEXT_BASE[104];
			link.l2.go = "Wine_Repeat1_goaway";
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = DLG_TEXT_BASE[105]+DLG_TEXT_BASE[106]+pchar.questTemp.Wine.Name+DLG_TEXT_BASE[107];
			link.l1 = DLG_TEXT_BASE[108];
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = DLG_TEXT_BASE[109];
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = DLG_TEXT_BASE[110];
			link.l1 = DLG_TEXT_BASE[111]+ NPCharSexPhrase(npchar, "","") +DLG_TEXT_BASE[112];
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
		break;
		// <-- мини-квест Дефицитный товар
		
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+DLG_TEXT_BASE[113]+ NPCharSexPhrase(npchar, "","") +".";
			link.l1 = DLG_TEXT_BASE[114]+pchar.GenQuest.Device.Shipyarder.Describe+DLG_TEXT_BASE[115];
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = DLG_TEXT_BASE[116]+ NPCharSexPhrase(npchar, "","") +DLG_TEXT_BASE[117];
				link.l1 = DLG_TEXT_BASE[118];
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[119];
				link.l1 = DLG_TEXT_BASE[120];
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+drand(30)+drand(40))
			{
				dialog.text = DLG_TEXT_BASE[121];
				link.l1 = DLG_TEXT_BASE[122];
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[123],DLG_TEXT_BASE[124],DLG_TEXT_BASE[125]);
				link.l1 = DLG_TEXT_BASE[126];
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = DLG_TEXT_BASE[127];
			link.l1 = DLG_TEXT_BASE[128];
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================

		case "AscoldMerchant": 
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(DLG_TEXT_BASE[19], DLG_TEXT_BASE[20], DLG_TEXT_BASE[21]),
                     LinkRandPhrase(DLG_TEXT_BASE[22], DLG_TEXT_BASE[23], DLG_TEXT_BASE[24]),
                     LinkRandPhrase(NPCharSexPhrase(npchar, DLG_TEXT_BASE[25], DLG_TEXT_BASE[26]),
                                    NPCharSexPhrase(npchar, DLG_TEXT_BASE[27], DLG_TEXT_BASE[28]),
                                    DLG_TEXT_BASE[29]),
                     LinkRandPhrase(DLG_TEXT_BASE[30], DLG_TEXT_BASE[31], DLG_TEXT_BASE[32]), "quest", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[33],
                                               DLG_TEXT_BASE[34],
                                               DLG_TEXT_BASE[35],
                                               DLG_TEXT_BASE[36], npchar, Dialog.CurrentNode);
            link.l1.go = DialogGoNodeRepeat("AscoldMerchant_2", "AscoldMerchant_3", "AscoldMerchant_4", "", npchar, Dialog.CurrentNode);
		break;
		
		case "AscoldMerchant_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[37],
                     NPCharSexPhrase(npchar, DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]),
                     NPCharSexPhrase(npchar, DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]));
			Link.l1 = DLG_TEXT_BASE[42];
			Link.l1.go = "exit";
		break;
		
		case "AscoldMerchant_3":
			dialog.text = LinkRandPhrase(NPCharSexPhrase(npchar, DLG_TEXT_BASE[43], DLG_TEXT_BASE[44]),
                                    DLG_TEXT_BASE[45],
                                    NPCharSexPhrase(npchar, DLG_TEXT_BASE[46], DLG_TEXT_BASE[47]));
			Link.l1 = DLG_TEXT_BASE[48];
			Link.l1.go = "exit";
		break;
		
		case "AscoldMerchant_4":
			dialog.text = LinkRandPhrase(NPCharSexPhrase(npchar, DLG_TEXT_BASE[49], DLG_TEXT_BASE[50]),
                                    NPCharSexPhrase(npchar, DLG_TEXT_BASE[51], DLG_TEXT_BASE[52]),
                                    NPCharSexPhrase(npchar, DLG_TEXT_BASE[53], DLG_TEXT_BASE[54]));
			Link.l1 = NPCharSexPhrase(npchar, DLG_TEXT_BASE[55], DLG_TEXT_BASE[56]);
			Link.l1.go = "exit_angry";
		break;

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

  		case "exit_angry":
			NextDiag.CurrentNode = "AngryQuest_AscoldMerchant";
			DialogExit();
		break;

		case "AngryQuest_AscoldMerchant":
            Dialog.text = RandPhraseSimple(DLG_TEXT_BASE[57], DLG_TEXT_BASE[58]);
			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[59], DLG_TEXT_BASE[60]);
		    Link.l1.go = "AngryExitAgain";
		    //===>> квест јскольда, розыск порошка мумии.
            if (pchar.questTemp.Ascold == "Seek_powder" && rand(10) == 2 && !CheckAttribute(npchar, "Angree"))
            {
                Dialog.text =  DLG_TEXT_BASE[61];
    			Link.l1 = DLG_TEXT_BASE[62];
    		    Link.l1.go = "AngStep_1";
            }
            if (CheckAttribute(npchar, "angry.terms")) //мирилка по квесту јскольда через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms) && pchar.questTemp.Ascold != "Seek_powder")
                {
         			Dialog.text = NPCharSexPhrase(npchar, DLG_TEXT_BASE[63], DLG_TEXT_BASE[64]);
        			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[65], DLG_TEXT_BASE[66]);
        			Link.l1.go = "First time";
        			CharacterDelAngry(npchar);
                }
            }
			npchar.Angree = true;
    	break;
////////////////////////////////////////////////////////////////////////////////////////////////

		case "AngStep_1":
            Dialog.text = DLG_TEXT_BASE[67];
            if (sti(pchar.money) >= 1000)
            {
    			Link.l1 = DLG_TEXT_BASE[68];
    		    Link.l1.go = "exit";
    		    pchar.questTemp.Ascold = "PowderWasSeek";
    		    CharacterDelAngry(npchar);
    		    AddMoneyToCharacter(pchar, -1000);
    		    GiveItem2Character(Pchar,"Powder_mummie");
            }
            else
            {
    			Link.l1 = DLG_TEXT_BASE[69];
    		    Link.l1.go = "AngryExitAgain";
            }
    	break;
	}
}
