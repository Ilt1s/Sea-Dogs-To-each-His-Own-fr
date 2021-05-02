#include "SD\TEXT\DIALOGS\Quest_Mayor.h"void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_MR[167], DLG_TEXT_MR[168], DLG_TEXT_MR[169]), 
					LinkRandPhrase(DLG_TEXT_MR[170]+ GetSexPhrase(DLG_TEXT_MR[171],"") +"!", DLG_TEXT_MR[172], DLG_TEXT_MR[173]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_MR[174], DLG_TEXT_MR[175]), 
					RandPhraseSimple(DLG_TEXT_MR[176], DLG_TEXT_MR[177]));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = DLG_TEXT_MR[178];
				link.l1 = DLG_TEXT_MR[179];
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + DLG_TEXT_MR[180] +GetFullName(npchar)+ DLG_TEXT_MR[181] + NationKingsName(npchar)+ DLG_TEXT_MR[182] + GetAddress_Form(NPChar) + ".";
				link.l1 = DLG_TEXT_MR[183] + pchar.lastname + DLG_TEXT_MR[184];
				link.l1.go = "info";
				link.l2 = DLG_TEXT_MR[183] + pchar.lastname + DLG_TEXT_MR[185];
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = DLG_TEXT_MR[186]+DLG_TEXT_MR[187]+DLG_TEXT_MR[188]+DLG_TEXT_MR[189]+DLG_TEXT_MR[190]+DLG_TEXT_MR[191]+DLG_TEXT_MR[192]+DLG_TEXT_MR[193];
			link.l1 = DLG_TEXT_MR[194];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = DLG_TEXT_MR[195];
			link.l1 = DLG_TEXT_MR[196];			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = DLG_TEXT_MR[197]+ GetSexPhrase(DLG_TEXT_MR[198],DLG_TEXT_MR[199]) +"...";
			link.l1 = LinkRandPhrase(DLG_TEXT_MR[200], DLG_TEXT_MR[201], DLG_TEXT_MR[202]);
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
