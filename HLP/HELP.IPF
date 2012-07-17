
.*---------------------------------------------------------------
.* A sample IPF file -- source for a help (.HLP) file.
.*---------------------------------------------------------------

:userdoc.

.nameit symbol=product text='MakMan/2'
.*--------------------------------
:h1 id=mainwin res=100.&product.
:i1.general help
:i1.about the &product.
:p.
This is general help for the &product..
:p.
The &product. has features that are common to most
:link reftype=fn refid=IBMtrade.Presentation Manager:elink.
(PM) programs, like a menu bar containing 
:link reftype=hd refid=file.File:elink. and
:link reftype=hd refid=edit.Edit:elink. 
and :hp2.Help:ehp2. action bar items.  You can use the &product.
as a template from which to build your own PM applications.
:p.
The &product. is fully help-enabled, and uses string resources,
instead of string literals, to facilitate translation.
:p.
To use the &product., open a file by selecting 
:link reftype=hd refid=open.Open:elink. from
the :hp2.File:ehp2. pull-down.  The file is opened, and then immediately closed.
Subsequently, any menu item you select is displayed as text in the client 
window.
.*--------------------------------
:fn id=IBMtrade.
:p.
A trademark of the IBM Corporation.
:efn.
.*--------------------------------
:h1 id=file res=110.File
:i1.file
:p.
Help for :hp2.File:ehp2..
.*--------------------------------
:h2 id=open res=130.Open
:i1.open
:i1.opening files
:p.
Help for :hp2.Open:ehp2. menu item.
.*--------------------------------
:h2 id=opendlg res=135.File open
:i1.file open dialog
:i1 id=dialog.dialog
:i2 refid=dialog.file open
:p.
Help for :hp2.File open:ehp2. dialog.
:p.
Enter the name of the file to open in the :hp2.Open filename:ehp2.
entry field.
.*--------------------------------
:h2 id=save res=140.Save
:i1.save
:p.
Help for :hp2.Save:ehp2..
.*--------------------------------
:h2 id=saveas res=150.Save as
:i1.save as
:p.
Help for :hp2.Save as:ehp2. menu item.
.*--------------------------------
:h2 id=savedlg res=155.Save as
:i1.save as dialog
:i2 refid=dialog.save as
:p.
Help for :hp2.Save as:ehp2. dialog.
:p.
Enter the name of the file to save in the :hp2.Save as filename:ehp2.
entry field.
.*--------------------------------
:h2 id=print res=160.Print
:i1.print
:p.
Help for :hp2.Print:ehp2..
.*--------------------------------
:h2 id=close res=170.Close
:i1.close
:p.
Help for :hp2.Close:ehp2..
.*--------------------------------
:h1 id=edit res=180.Edit
:i1.edit
:p.
Help for :hp2.Edit:ehp2..
.*--------------------------------
:h2 id=undo res=190.Undo 
:i1.undo
:p.
Help for :hp2.Undo:ehp2..
.*--------------------------------
:h2 id=copy res=200.Copy
:i1.copy
:p.
Help for :hp2.Copy:ehp2..
.*--------------------------------
:h2 id=cut res=210.Cut
:i1.cut
:p.
Help for :hp2.Cut:ehp2..
.*--------------------------------
:h2 id=paste res=220.Paste
:i1.paste
:p.
Help for :hp2.Paste:ehp2..
.*--------------------------------
:h2 id=find res=230.Find 
:i1.find
:p.
Help for :hp2.Find:ehp2..
.*--------------------------------
:h2 id='findnext' res=240.Find next
:i1.find next
:p.
Help for :hp2.Find next:ehp2..
.*---------------------------------

:euserdoc.











