#include "SD\TEXT\DIALOGS\Quest_Prison.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = DLG_TEXT_PRS[0];
			link.l1 = DLG_TEXT_PRS[1];
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = DLG_TEXT_PRS[55];
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = DLG_TEXT_PRS[56];
				link.l1.go = "caleuche_3";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = DLG_TEXT_PRS[57];
				link.l1.go = "caleuche_7";
			}
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = DLG_TEXT_PRS[58];
			link.l1 = DLG_TEXT_PRS[59];
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = DLG_TEXT_PRS[60];
			link.l1 = DLG_TEXT_PRS[61];
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = DLG_TEXT_PRS[62];
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = DLG_TEXT_PRS[63];
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = DLG_TEXT_PRS[64];
			dialog.text = DLG_TEXT_PRS[65];
			link.l1 = DLG_TEXT_PRS[66]+sTime+DLG_TEXT_PRS[67];
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = DLG_TEXT_PRS[68];
			link.l1 = DLG_TEXT_PRS[69];
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = DLG_TEXT_PRS[70];
			link.l1 = DLG_TEXT_PRS[71];
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddQuestRecord("Caleuche", "15");
			pchar.questTemp.Caleuche.Bandos = "comendant";
			pchar.questTemp.Caleuche.BelizChance = drand(3);
			SetFunctionTimerCondition("Caleuche_BelizRegard", 0, 0, 3, false); // таймер
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = DLG_TEXT_PRS[72];
				link.l1 = DLG_TEXT_PRS[73];
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = DLG_TEXT_PRS[74];
				link.l1 = DLG_TEXT_PRS[75];
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = DLG_TEXT_PRS[76];
			link.l1 = DLG_TEXT_PRS[77];
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = DLG_TEXT_PRS[78];
			link.l1 = DLG_TEXT_PRS[79];
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = DLG_TEXT_PRS[80];
			link.l1 = DLG_TEXT_PRS[81];
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = DLG_TEXT_PRS[82];
			link.l1 = DLG_TEXT_PRS[83];
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info(DLG_TEXT_PRS[84]);
			Log_Info(DLG_TEXT_PRS[85]);
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = DLG_TEXT_PRS[86];
			link.l1 = DLG_TEXT_PRS[87];
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
