Object subclass: #ClassMapping
	self subclassResponsibility! !
	self subclassResponsibility! !
	self subclassResponsibility! !
	self subclassResponsibility! !
	self subclassResponsibility! !
	self subclassResponsibility! !
	self subclassResponsibility! !
	self subclassResponsibility ! !
	self subclassResponsibility! !
	self subclassResponsibility! !
	self error: self class invalidAddressRecordErrorDescription ! !
	self error: self class invalidRecordTypeErrorDescription! !
	self subclassResponsibility! !
	^self new initializeOn: aReadStream on: aSystem! !
	^'Invalid address record'! !
	^'Invalid record type'! !