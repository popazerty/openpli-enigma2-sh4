from enigma import eLabel

# Calls onto the static function in eLabel. This avoids causing an invalidate
<<<<<<< HEAD
# on the parent container which is detrimental to UI performance, 
# particularly in a complex screen like the graph EPG
=======
# on the parent container which is detrimental to UI performance,
# particularly in a complex screen like the graph EPG


>>>>>>> 4cf2ad3c93680791dc065098aeaec5f28fef9daf
def getTextBoundarySize(instance, font, targetSize, text):
	return eLabel.calculateTextSize(font, text, targetSize)
