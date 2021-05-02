#include "SD\TEXT\DIALOGS\Quest_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[73]+ GetCityName(npchar.city) +DLG_TEXT_STR[74],
                          DLG_TEXT_STR[75], DLG_TEXT_STR[76],
                          DLG_TEXT_STR[77], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[78] + NPChar.name + DLG_TEXT_STR[79], DLG_TEXT_STR[80],
                      DLG_TEXT_STR[81], DLG_TEXT_STR[82], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = DLG_TEXT_STR[96];
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = DLG_TEXT_STR[97];
				link.l1.go = "caleuche";
			}
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase(DLG_TEXT_STR[98],DLG_TEXT_STR[99],DLG_TEXT_STR[100]);
			link.l1 = DLG_TEXT_STR[101];
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = DLG_TEXT_STR[102];
			link.l1 = DLG_TEXT_STR[103];
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = DLG_TEXT_STR[104];
			link.l1 = DLG_TEXT_STR[105];
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = DLG_TEXT_STR[106];
			link.l1 = DLG_TEXT_STR[107];
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

