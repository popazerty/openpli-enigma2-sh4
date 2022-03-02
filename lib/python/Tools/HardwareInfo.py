from Tools.Directories import SCOPE_SKIN, resolveFilename

hw_info = None


class HardwareInfo:
	device_name = _("unavailable")
	device_brandname = None
	device_model = None
	device_version = ""
	device_revision = ""
	device_hdmi = True

	def __init__(self):
		global hw_info
		if hw_info:
			return
		hw_info = self

		print "[HardwareInfo] Scanning hardware info"
		# Version
		try:
			self.device_version = open("/proc/stb/info/version").read().strip()
		except:
			pass

		# Revision
		try:
			self.device_revision = open("/proc/stb/info/board_revision").read().strip()
		except:
			pass

		# Name ... bit odd, but history prevails
		try:
			self.device_name = open("/proc/stb/info/model").read().strip()
		except:
			pass

		# Brandname ... bit odd, but history prevails
		try:
			self.device_brandname = open("/proc/stb/info/brandname").read().strip()
		except:
			pass

		# Model
		try:
			self.device_model = open("/proc/stb/info/boxtype").read().strip()
		except:
			pass

		# standard values
		self.device_model = self.device_model or self.device_name
		self.device_hw = self.device_model
		self.machine_name = self.device_model

<<<<<<< HEAD
		self.machine_name = self.device_model

		self.device_string = self.device_model

		# only some early DMM boxes do not have HDMI hardware
#		self.device_hdmi =  self.device_model not in ("dm800", "dm8000")
=======
		# custom overrides for specific receivers
		if self.device_model.startswith(("et9", "et4", "et5", "et6", "et7")):
			self.machine_name = "%sx00" % self.device_model[:3]
		elif self.device_model == "et11000":
			self.machine_name = "et1x000"
		elif self.device_brandname == "Zgemma":
			if self.device_model and self.device_name and "H9Twin" in self.device_model and "combo" in self.device_name:
				self.device_model = self.device_model.lower().replace(" ", "")
			else:
				self.device_model = self.device_name
			self.machine_name = self.device_name

		if self.device_revision:
			self.device_string = "%s (%s-%s)" % (self.device_hw, self.device_revision, self.device_version)
		elif self.device_version:
			self.device_string = "%s (%s)" % (self.device_hw, self.device_version)
		else:
			self.device_string = self.device_hw

		# only some early DMM boxes do not have HDMI hardware
		self.device_hdmi = self.device_model not in ("dm800", "dm8000")
>>>>>>> 4cf2ad3c93680791dc065098aeaec5f28fef9daf

		print "Detected: " + self.get_device_string()

	def get_device_name(self):
		return hw_info.device_name

	def get_device_model(self):
		return hw_info.device_model

	def get_device_version(self):
		return hw_info.device_version

	def get_device_revision(self):
		return hw_info.device_revision

	def get_device_string(self):
		return hw_info.device_string

	def get_machine_name(self):
		return hw_info.machine_name

	def has_hdmi(self):
		return hw_info.device_hdmi
