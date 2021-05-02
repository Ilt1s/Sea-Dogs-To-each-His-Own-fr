#include "SD\TEXT\DIALOGS\Quest_Brothel.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BR[0], DLG_TEXT_BR[1]), DLG_TEXT_BR[2], DLG_TEXT_BR[3],
                          DLG_TEXT_BR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BR[5], DLG_TEXT_BR[6]), DLG_TEXT_BR[7],
                      DLG_TEXT_BR[8], DLG_TEXT_BR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				link.l1 = DLG_TEXT_BR[28];
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = DLG_TEXT_BR[29];
			link.l1 = DLG_TEXT_BR[30];
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = DLG_TEXT_BR[31];
			link.l1 = DLG_TEXT_BR[32];
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = DLG_TEXT_BR[33];
			link.l1 = DLG_TEXT_BR[34];
			link.l1.go = "Gigolo_2_1";
			link.l2 = DLG_TEXT_BR[35];
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = DLG_TEXT_BR[36];
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = DLG_TEXT_BR[37];
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = DLG_TEXT_BR[38];
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = DLG_TEXT_BR[39];
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = DLG_TEXT_BR[40];
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = DLG_TEXT_BR[41];
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = DLG_TEXT_BR[42];
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = DLG_TEXT_BR[43];
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = DLG_TEXT_BR[44];
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = DLG_TEXT_BR[45];
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = DLG_TEXT_BR[46];
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = DLG_TEXT_BR[47];
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = DLG_TEXT_BR[48]+DLG_TEXT_BR[49];
			link.l1 = DLG_TEXT_BR[50];
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

