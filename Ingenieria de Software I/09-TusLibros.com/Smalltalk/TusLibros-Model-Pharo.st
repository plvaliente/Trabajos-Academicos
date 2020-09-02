Object subclass: #Cart

	aQuantity strictlyPositive ifFalse: [self signalInvalidQuantity ]! !

	(catalog includesKey: anItem) ifFalse: [ self signalInvalidItem ]! !
	
	^self class invalidItemErrorMessage ! !
	
	^self class invalidQuantityErrorMessage ! !

	catalog := aCatalog.
	items := Bag new.! !

	self assertIsValidQuantity: aQuantity.
	self assertIsValidItem: anItem.

	items add: anItem withOccurrences: aQuantity ! !

	^ self add: 1 of: anItem ! !

	^items includes: anItem ! !
	
	^items isEmpty ! !

	self error: self invalidItemErrorMessage! !

	self error: self invalidQuantityErrorMessage ! !

	^items occurrencesOf: anItem  ! !
	
	^items copy! !
	
	^ items contents keysAndValuesDo: [ :anItem :aQuantity | aBlock value: anItem value: aQuantity ]! !
	
	^ catalog! !

	^self new initializeAcceptingItemsOf: aCatalog ! !
	
	^'Item is not in catalog'! !
	
	^'Invalid number of items'! !
	
	self error: systemFacade sessionHasExpiredErrorDescription ! !

	^(Cashier 
		toCheckout: cart 
		ownedBy: owner
		charging: (CreditCard expiringOn: anExpirationMonthOfYear) 
		throught: systemFacade merchantProcessor 
		on: self today 
		registeringOn: systemFacade salesBook) checkOut ! !

	^cart content! !

	^cart add: anAmount of: aBook! !

	owner := aCustomer.
	cart := aCart.
	systemFacade := aSystemFacade.
	lastUsedTime := self now.! !

	| now |

	now := self now.
	self assertIsNotExpirtedAt: now.
	
	^ [ aBlock value: self ] ensure: [ lastUsedTime := now  ]! !

	^systemFacade now! !

	^systemFacade today! !

	(self isExpiredAt: aTime) ifTrue: [ self signalCartSessionExpired ]! !
	
	^ (lastUsedTime + systemFacade sessionDuration) < aTime! !

	^self new initializeOwnedBy: aCustomer with: aCart on: aSystemFacade! !

	merchantProcessor debit: ticket total from: creditCard.
	! !

	salesBook add: self createSale! !

	^(cart catalog at: anItem) * aQuantity  ! !

	^ Sale doneBy: owner certifiedWith: ticket
! !

	| lineItems |
	
	lineItems := OrderedCollection new.
	cart itemsAndQuantitiesDo: [ :anItem :aQuantity | 
		lineItems add: (self createLineItemOf: anItem quantity: aQuantity)].
	
	ticket := Ticket of: lineItems 
	! !

	^LineItem of: anItem quantity: aQuantity total: (self totalOf: anItem quantity: aQuantity) ! !
	
	cart := aCart.
	owner := anOwner.
	creditCard := aCreditCard.
	merchantProcessor := aMerchantProcessor.
	salesBook := aSalesBook! !

	self createTicket.
	self debitTotal.
	self registerSale.

	^ ticket ! !
	
	aCart isEmpty ifTrue: [self signalCartCanNotBeEmpty ]! !
	
	(aCreditCard isExpiredOn: aDate) ifTrue: [self signalCanNotChargeAnExpiredCreditCard]! !

	self error: self cartCanNotBeEmptyErrorMessage! !

	 self error: self canNotChargeAnExpiredCreditCardErrorMessage ! !
	
	self assertIsNotEmpty: aCart.
	self assertIsNotExpired: aCreditCard on: aDate.
	
	^self new initializeToCheckout: aCart ownedBy: anOwner charging: aCreditCard throught: aMerchantProcessor registeringOn: aSalesBook! !
	
	^'Can not charge an expired credit card'! !
	
	^'Can not check out an empty cart'! !
	
	^'Credit card has no credit'! !

	self subclassResponsibility ! !

	self subclassResponsibility ! !
	
	^expiration start < (Month month: aDate monthIndex year: aDate year) start ! !
	
	expiration := aMonth ! !
	
	^self new initializeExpiringOn: aMonth! !

	item := anItem.
	quantity := aQuantity.
	total := aTotal 

! !
	
	^ total! !
	
	^ item! !

	^self new initializeOf: anItem quantity: aQuantity total: aTotal

! !

	"Aunque nadie subclasifica esta clase, esta para definir el protocolo que se espera que todo MerchantProcessor sepa responder - Hernan"! !

	self subclassResponsibility ! !

	^customer = aCustomer ! !
	
	^ ticket total! !
	
	^ticket lineItemsDo: aBlock ! !

	customer := aCustomer.
	ticket := aTicket ! !

	^self new initializeDoneBy: aCustomer certifiedWith: aTicket ! !
	
	^lineItems sum: [ :aLineItem | aLineItem total]! !

	lineItems := aCollectionOfLineItems ! !
	
	^lineItems do: aBlock ! !

	^self new initializeOf: aCollectionOfLineItems ! !

	"Esto es un indicio de que por ahi conviene empezar a pensar en modelar un SaleBook - Hernan"
	aSale lineItemsDo: [ :aLineItem | | oldTotal newTotal |
		oldTotal := salesOrderedByBook at: aLineItem item ifAbsentPut: [ 0 ].
		newTotal := oldTotal + aLineItem total.
		salesOrderedByBook at: aLineItem item put: newTotal ]! !

	"Esto es un indicio de que por ahi conviene empezar a pensar en modelar un SaleBook - Hernan"
	^ salesBook select: [ :aSale | aSale wasDoneBy: aUser ]! !
	
	^clock now! !
	
	^clock today! !
	acceptingItemsOf: aCatalog 
	registeringOn: aSalesBook 
	debitingThrought: aMerchantProcessor 
	measuringTimeWith: aClock

	validUsersAndPasswords := aValidUsersAndPasswords.
	catalog := aCatalog.
	salesBook := aSalesBook.
	merchantProcessor := aMerchantProcessor.
	clock := aClock.
	
	cartSessions := Dictionary new.
	lastId := 0.! !

	^ merchantProcessor! !

	^ salesBook! !
	
	^Cashier canNotChargeAnExpiredCreditCardErrorMessage ! !
	
	^'Invalid user and/or password'! !
	
	^Cart invalidItemErrorMessage ! !
	
	^'Invalid cart id'! !
	
	^'Can not use the cart after ', self sessionDuration minutes printString , ' minutes of inactivity'! !
	
	^Cashier cartCanNotBeEmptyErrorMessage ! !
	
	"Recuerden que esto es un ejemplo, por lo que voy a generar ids numericos consecutivos, pero en una 
	implementacion real no deberian se numeros consecutivos ni nada que genere problemas de seguridad - Hernan"
	
	lastId := lastId + 1.
	^lastId! !
	
	^30 minutes! !

	| cartSession |
	
	cartSession := cartSessions at: aCartId ifAbsent: [self signalInvalidCartId ].
	^cartSession do: aBlock
! !
	
	self error: self invalidUserAndOrPasswordErrorDescription! !
	
	self error: self invalidCartIdErrorDescription ! !

	"Recordar que esto es solo un ejemplo. No se deben guardar passwords en un sistema de verdad sino un
	hash o similar - Hernan"
	
	| storedPassword |
	
	storedPassword := validUsersAndPasswords at: aUser ifAbsent: [ ^false ].
	^aPassword = storedPassword ! !

	^ (self does: aUser authenticatesWith: aPassword) 
		ifTrue: aBlock 
		ifFalse: [ self signalInvalidUserAndOrPassword ].
	! !

	self 
		withCartSessionIdentifiedAs: aCartId 
		do: [ :cartSession | cartSession 
			checkOutCartWithCreditCardNumbered: aCreditCartNumber 
			ownedBy: anOwner 
			expiringOn: anExpirationMonthOfYear ]
! !

	^ self if: aUser authenticatesWith: aPassword do: [ | cartId cartSession |
	
		cartId := self generateCartId.
		cartSession := CartSession ownedBy: aUser with: (Cart acceptingItemsOf: catalog) on: self..
		cartSessions at: cartId put: cartSession.
	
		cartId  ]! !

	^self if: aUser authenticatesWith: aPassword do: [	| sales |
		sales := self salesDoneBy: aUser.	
		sales
			inject: Dictionary new
			into: [ :salesOrderedByBook :aSale | 
				self list: aSale on: salesOrderedByBook.
				salesOrderedByBook ] ]! !

	self withCartSessionIdentifiedAs: aCartId do: [ :cartSession | cartSession addToCart: anAmount of: aBook ]! !

	^ self withCartSessionIdentifiedAs: aCartId do: [ :cartSession | cartSession cartContent ]! !
	acceptingItemsOf: aCatalog 
	registeringOn: aSalesBook 
	debitingThrought: aMerchantProcessor 
	measuringTimeWith: aClock

	^self new 
		initializeAuthenticatingWith: aValidUsersAndPasswords 
		acceptingItemsOf: aCatalog 
		registeringOn: aSalesBook 
		debitingThrought: aMerchantProcessor 
		measuringTimeWith: aClock! !