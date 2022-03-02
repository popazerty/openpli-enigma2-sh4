from Components.Label import Label
from Components.VolumeBar import VolumeBar
from Screens.Screen import Screen
<<<<<<< HEAD
=======

>>>>>>> 4cf2ad3c93680791dc065098aeaec5f28fef9daf

class Volume(Screen):
	def __init__(self, session):
		Screen.__init__(self, session)
		self.volumeBar = VolumeBar()
		self["Volume"] = self.volumeBar
		self["VolumeText"] = Label("")

	def setValue(self, vol):
		print "[Volume] Volume set to %d." % vol
		self.volumeBar.setValue(vol)
		self["VolumeText"].text = str(vol)
