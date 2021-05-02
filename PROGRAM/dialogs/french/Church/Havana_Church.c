#include "SD\TEXT\DIALOGS\Quest_church.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CHR[0], DLG_TEXT_CHR[1]), DLG_TEXT_CHR[2], DLG_TEXT_CHR[3],
                          DLG_TEXT_CHR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CHR[5], DLG_TEXT_CHR[6]), DLG_TEXT_CHR[7],
                      DLG_TEXT_CHR[8], DLG_TEXT_CHR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = DLG_TEXT_CHR[56]+sld.name+DLG_TEXT_CHR[57];
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = DLG_TEXT_CHR[58];
				link.l1.go = "caleuche_4";
			}
		break;
		
		case "caleuche":
			dialog.text = DLG_TEXT_CHR[59];
			link.l1 = DLG_TEXT_CHR[60];
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = DLG_TEXT_CHR[61];
			link.l1 = DLG_TEXT_CHR[62];
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = DLG_TEXT_CHR[63];
			link.l1 = DLG_TEXT_CHR[64]+npchar.name+DLG_TEXT_CHR[65];
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info(DLG_TEXT_CHR[66]);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = DLG_TEXT_CHR[67];
			link.l1 = DLG_TEXT_CHR[68];
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = DLG_TEXT_CHR[69];
			link.l1 = DLG_TEXT_CHR[70]+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info(DLG_TEXT_CHR[71]);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = DLG_TEXT_CHR[72];
			link.l1 = DLG_TEXT_CHR[73];
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = DLG_TEXT_CHR[74];
			link.l1 = DLG_TEXT_CHR[75]+npchar.name+DLG_TEXT_CHR[76];
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = DLG_TEXT_CHR[77];
			link.l1 = DLG_TEXT_CHR[78]+sld.name+DLG_TEXT_CHR[79];
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = DLG_TEXT_CHR[80];
			link.l1 = DLG_TEXT_CHR[81];
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = DLG_TEXT_CHR[82];
			link.l1 = DLG_TEXT_CHR[83];
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = DLG_TEXT_CHR[84];
			link.l1 = DLG_TEXT_CHR[85]+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



