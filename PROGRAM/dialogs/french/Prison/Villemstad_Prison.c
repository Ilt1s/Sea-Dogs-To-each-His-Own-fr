#include "SD\TEXT\DIALOGS\Quest_Prison.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = DLG_TEXT_PRS[0];
			link.l1 = DLG_TEXT_PRS[1];
			link.l1.go = "Exit";
			//����������
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = DLG_TEXT_PRS[2];
                link.l1.go = "Portugal";
            }
		break;
		
		//����������
		case "Portugal":
			dialog.text = DLG_TEXT_PRS[3];
			link.l1 = DLG_TEXT_PRS[4];
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = DLG_TEXT_PRS[5];
			link.l1 = DLG_TEXT_PRS[6];
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			pchar.quest.InMarigoResidenceOver.over = "yes"; //����� ������
			InterfaceStates.Buttons.Save.enable = false;//��������� �����������
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
