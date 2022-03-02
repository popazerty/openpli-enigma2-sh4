from Plugins.Plugin import PluginDescriptor


def CutListEditor(session, service=None):
	import ui
	return ui.CutListEditor(session, service)


def main(session, service, **kwargs):
	session.open(CutListEditor, service)


def Plugins(**kwargs):
<<<<<<< HEAD
	return PluginDescriptor(name= _("Cutlist editor"), description=_("Cutlist editor..."),
		where = PluginDescriptor.WHERE_MOVIELIST, needsRestart = False, fnc=main)
=======
	return PluginDescriptor(name=_("Cutlist editor"), description=_("Cutlist editor..."),
		where=PluginDescriptor.WHERE_MOVIELIST, needsRestart=False, fnc=main)
>>>>>>> 4cf2ad3c93680791dc065098aeaec5f28fef9daf
