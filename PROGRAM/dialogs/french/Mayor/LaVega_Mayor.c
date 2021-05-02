#include "SD\TEXT\DIALOGS\Quest_Mayor.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывани€
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. ¬ npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ƒиалог первый - перва€ встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_MR[323],
                         DLG_TEXT_MR[324], DLG_TEXT_MR[325],
                         DLG_TEXT_MR[326], "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_MR[327],
                                               DLG_TEXT_MR[328]+npchar.name+"...",
                                               DLG_TEXT_MR[329]+npchar.name+"...",
                                               DLG_TEXT_MR[330], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + DLG_TEXT_MR[331],
                         DLG_TEXT_MR[332], DLG_TEXT_MR[333],
                         DLG_TEXT_MR[334], "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_MR[335],
                                               DLG_TEXT_MR[336],
                                               DLG_TEXT_MR[337]+npchar.name+DLG_TEXT_MR[338],
                                               DLG_TEXT_MR[339], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== √рабеж среди бела дн€, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_MR[340], DLG_TEXT_MR[341]);
			link.l1 = LinkRandPhrase(DLG_TEXT_MR[342],DLG_TEXT_MR[343],DLG_TEXT_MR[344]);
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase(DLG_TEXT_MR[345],DLG_TEXT_MR[346]) +DLG_TEXT_MR[347],DLG_TEXT_MR[348]);
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примир€емс€ через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_MR[349];
        			link.l1 = DLG_TEXT_MR[350];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = DLG_TEXT_MR[351];
			link.l1 = RandPhraseSimple(DLG_TEXT_MR[352], DLG_TEXT_MR[353]);
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примир€емс€ через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_MR[354];
        			link.l1 = ""+npchar.name+DLG_TEXT_MR[355];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
