#include "SD\TEXT\DIALOGS\Quest_usurer.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[0], DLG_TEXT_USR[1]), DLG_TEXT_USR[2], DLG_TEXT_USR[3],
                          DLG_TEXT_USR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[5], DLG_TEXT_USR[6]), DLG_TEXT_USR[7],
                      DLG_TEXT_USR[8], DLG_TEXT_USR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = DLG_TEXT_USR[135]+GetFullName(pchar)+DLG_TEXT_USR[136];
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = DLG_TEXT_USR[137]+GetFullName(pchar)+DLG_TEXT_USR[138];
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = DLG_TEXT_USR[139]+GetFullName(pchar)+DLG_TEXT_USR[140];
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = DLG_TEXT_USR[141]+GetFullName(pchar)+DLG_TEXT_USR[142];
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = DLG_TEXT_USR[143]+GetFullName(pchar)+DLG_TEXT_USR[144];
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = DLG_TEXT_USR[145]+GetFullName(pchar)+DLG_TEXT_USR[146];
			link.l1 = DLG_TEXT_USR[147];
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			Log_Info(DLG_TEXT_USR[148]);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = DLG_TEXT_USR[149];
			link.l1 = DLG_TEXT_USR[150];
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = DLG_TEXT_USR[151];
			link.l1 = DLG_TEXT_USR[152];
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = DLG_TEXT_USR[153];
			link.l1 = DLG_TEXT_USR[154];
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = DLG_TEXT_USR[155];
			link.l1 = DLG_TEXT_USR[156];
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = DLG_TEXT_USR[157];
			link.l1 = DLG_TEXT_USR[158];
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = DLG_TEXT_USR[159];
			link.l1 = DLG_TEXT_USR[160];
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = DLG_TEXT_USR[161];
			link.l1 = DLG_TEXT_USR[162];
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = DLG_TEXT_USR[163];
			link.l1 = DLG_TEXT_USR[164];
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = DLG_TEXT_USR[165];
			link.l1 = DLG_TEXT_USR[166];
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = DLG_TEXT_USR[167];
			link.l1 = DLG_TEXT_USR[168];
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = DLG_TEXT_USR[169];
			link.l1 = DLG_TEXT_USR[170];
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = DLG_TEXT_USR[171];
			link.l1 = DLG_TEXT_USR[172];
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
		break;
		
		case "FMQG_14":
			dialog.text = DLG_TEXT_USR[173];
			link.l1 = DLG_TEXT_USR[174];
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info(DLG_TEXT_USR[175]);
			Log_Info(DLG_TEXT_USR[176]);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = DLG_TEXT_USR[177];
			link.l1 = DLG_TEXT_USR[178];
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			dialog.text = DLG_TEXT_USR[179];
			link.l1 = DLG_TEXT_USR[180];
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = DLG_TEXT_USR[181];
			link.l1 = DLG_TEXT_USR[182];
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = DLG_TEXT_USR[183];
			link.l1 = DLG_TEXT_USR[184];
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = DLG_TEXT_USR[185];
			link.l1 = DLG_TEXT_USR[186];
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = DLG_TEXT_USR[187];
			link.l1 = DLG_TEXT_USR[188];
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = DLG_TEXT_USR[189];
			link.l1 = DLG_TEXT_USR[190];
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = DLG_TEXT_USR[191];
			link.l1 = DLG_TEXT_USR[192];
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = DLG_TEXT_USR[193];
			link.l1 = DLG_TEXT_USR[194];
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

