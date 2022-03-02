from Screens.Screen import Screen
from Components.config import config, ConfigSubsection, ConfigInteger

config.plugins.OSDPositionSetup = ConfigSubsection()
config.plugins.OSDPositionSetup.dst_left = ConfigInteger(default=0)
config.plugins.OSDPositionSetup.dst_width = ConfigInteger(default=720)
config.plugins.OSDPositionSetup.dst_top = ConfigInteger(default=0)
config.plugins.OSDPositionSetup.dst_height = ConfigInteger(default=576)


def setPosition(dst_left, dst_width, dst_top, dst_height):
	if dst_left + dst_width > 720:
		dst_width = 720 - dst_left
	if dst_top + dst_height > 576:
		dst_height = 576 - dst_top
	try:
		file = open("/proc/stb/vmpeg/0/dst_left", "w")
		file.write('%X' % dst_left)
		file.close()
		file = open("/proc/stb/vmpeg/0/dst_width", "w")
		file.write('%X' % dst_width)
		file.close()
		file = open("/proc/stb/vmpeg/0/dst_top", "w")
		file.write('%X' % dst_top)
		file.close()
		file = open("/proc/stb/vmpeg/0/dst_height", "w")
		file.write('%X' % dst_height)
		file.close()
	except:
		return


def setConfiguredPosition():
	setPosition(int(config.plugins.OSDPositionSetup.dst_left.value), int(config.plugins.OSDPositionSetup.dst_width.value), int(config.plugins.OSDPositionSetup.dst_top.value), int(config.plugins.OSDPositionSetup.dst_height.value))


def main(session, **kwargs):
	from overscanwizard import OverscanWizard
	session.open(OverscanWizard, timeOut=False)


def startSetup(menuid):
	return menuid == "video" and [(_("Overscan wizard"), main, "sd_position_setup", 0)] or []


def startup(reason, **kwargs):
	setConfiguredPosition()


def Plugins(**kwargs):
	from Plugins.Plugin import PluginDescriptor
<<<<<<< HEAD
	return [PluginDescriptor(name = _("Overscan wizard"), description = "", where = PluginDescriptor.WHERE_SESSIONSTART, fnc = startup),
		PluginDescriptor(name = _("Overscan wizard"), description = _("Wizard to arrange the overscan"), where = PluginDescriptor.WHERE_MENU, fnc = startSetup)]
=======
	return [PluginDescriptor(name=_("Overscan wizard"), description="", where=PluginDescriptor.WHERE_SESSIONSTART, fnc=startup),
		PluginDescriptor(name=_("Overscan wizard"), description=_("Wizard to arrange the overscan"), where=PluginDescriptor.WHERE_MENU, fnc=startSetup)]
>>>>>>> 4cf2ad3c93680791dc065098aeaec5f28fef9daf
