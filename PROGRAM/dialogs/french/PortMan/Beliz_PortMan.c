#include "SD\TEXT\DIALOGS\Quest_Portman.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//������
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = DLG_TEXT_PRT[77];
				link.l1 = DLG_TEXT_PRT[78];
				link.l1.go = "Regata_check";
				break;
			}
			//������
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[0], DLG_TEXT_PRT[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_PRT[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_PRT[3],
                          DLG_TEXT_PRT[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[5], DLG_TEXT_PRT[6]), DLG_TEXT_PRT[7],
                      DLG_TEXT_PRT[8], DLG_TEXT_PRT[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		//������
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//�������� �� ������� ������� � �����
		{
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER || pchar.Ship.Name != "S�nt� �ath�rina")
			{
			dialog.text = DLG_TEXT_PRT[79];
			link.l1 = DLG_TEXT_PRT[80];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//�������� �� � ����� �� 1 �������
			dialog.text = DLG_TEXT_PRT[81]+ GetFullName(pchar) +DLG_TEXT_PRT[82]+pchar.Ship.Name+DLG_TEXT_PRT[83]+sti(pchar.questTemp.Regata.FirstTransitionTime)+DLG_TEXT_PRT[84];
			link.l1 = DLG_TEXT_PRT[85];
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = DLG_TEXT_PRT[86];
			link.l1 = DLG_TEXT_PRT[87];
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//��� ���������� ����������
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//��� �������
				}
			}
			if (n==1)
			{
			dialog.text = DLG_TEXT_PRT[89];
			link.l1 = DLG_TEXT_PRT[90];
			link.l1.go = "exit";
			}
			else
			{
				if (n==6)
				{
				dialog.text = DLG_TEXT_PRT[91];
				link.l1 = DLG_TEXT_PRT[92];
				link.l1.go = "exit";
				}
				else
				{
					if (n==2)
					{
					dialog.text = DLG_TEXT_PRT[93]+sName+DLG_TEXT_PRT[94]+sShip+DLG_TEXT_PRT[95];
					link.l1 = DLG_TEXT_PRT[96];
					link.l1.go = "exit";
					}
					else
					{
					dialog.text = DLG_TEXT_PRT[97]+n+DLG_TEXT_PRT[98]+sName+DLG_TEXT_PRT[99]+sShip+".";
					link.l1 = DLG_TEXT_PRT[100];
					link.l1.go = "exit";
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//���������
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//������� ������
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//�������� 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//�������� 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//�������� 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//������ ������ � ��������
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//�� � ������
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//���� � �� �����
		break;
		//������
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}


