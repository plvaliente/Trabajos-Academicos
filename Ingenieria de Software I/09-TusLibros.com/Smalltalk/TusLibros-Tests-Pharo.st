TestCase subclass: #CartTest	instanceVariableNames: 'testObjectsFactory'	classVariableNames: ''	poolDictionaries: ''	category: 'TusLibros-Tests'!!CartTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/17/2013 18:11'!test06CartRemembersAddedItems

	| cart |
	
	cart := testObjectsFactory createCart.
	
	cart add: testObjectsFactory itemSellByTheStore.
	self assert: (cart includes: testObjectsFactory itemSellByTheStore)! !!CartTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/17/2013 18:10'!test05CanNotAddMoreThanOneItemNotSellByTheStore

	| cart |
	
	cart := testObjectsFactory createCart.
	
	self 
		should: [cart add: 2 of: testObjectsFactory itemNotSellByTheStore  ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = cart invalidItemErrorMessage.
			self assert: cart isEmpty ]! !!CartTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/17/2013 18:10'!test03AfterAddingAnItemTheCartIsNotEmptyAnymore

	| cart |
	
	cart := testObjectsFactory createCart.
	
	cart add: testObjectsFactory itemSellByTheStore.
	self deny: cart isEmpty ! !!CartTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/17/2013 18:11'!test07CartDoesNotHoldNotAddedItems

	| cart |
	
	cart := testObjectsFactory createCart.
	
	self deny: (cart includes: testObjectsFactory itemSellByTheStore)! !!CartTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/17/2013 18:10'!test01NewCartsAreCreatedEmpty

	self assert: testObjectsFactory createCart isEmpty! !!CartTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/17/2013 18:10'!test02CanNotAddItemsThatDoNotBelongToStore

	| cart |
	
	cart := testObjectsFactory createCart.
	
	self 
		should: [ cart add: testObjectsFactory itemNotSellByTheStore ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = cart invalidItemErrorMessage.
			self assert: cart isEmpty ]! !!CartTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/17/2013 18:11'!test08CartRemembersTheNumberOfAddedItems

	| cart |
	
	cart := testObjectsFactory createCart.
	
	cart add: 2 of: testObjectsFactory itemSellByTheStore.
	self assert: (cart occurrencesOf: testObjectsFactory itemSellByTheStore) = 2! !!CartTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/17/2013 18:10'!test04CanNotAddNonPositiveNumberOfItems

	| cart |
	
	cart := testObjectsFactory createCart.
	
	self 
		should: [cart add: 0 of: testObjectsFactory itemSellByTheStore ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = cart invalidQuantityErrorMessage.
			self assert: cart isEmpty ]! !!CartTest methodsFor: 'setup' stamp: 'HernanWilkinson 6/17/2013 18:09'!setUp 

	testObjectsFactory := StoreTestObjectsFactory new.! !TestCase subclass: #CashierTest	instanceVariableNames: 'testObjectsFactory debitBehavior'	classVariableNames: ''	poolDictionaries: ''	category: 'TusLibros-Tests'!!CashierTest methodsFor: 'setup' stamp: 'HernanWilkinson 6/17/2013 19:03'!setUp 

	testObjectsFactory := StoreTestObjectsFactory new.
	debitBehavior := [ :anAmount :aCreditCard | ]! !!CashierTest methodsFor: 'merchant processor protocol' stamp: 'HernanWilkinson 6/17/2013 19:02'!debit: anAmount from: aCreditCard 

	^debitBehavior value: anAmount value: aCreditCard ! !!CashierTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/22/2013 12:00'!test01CanNotCheckoutAnEmptyCart

	| salesBook |
	
	salesBook := OrderedCollection new.
	self 
		should: [ Cashier 
			toCheckout: testObjectsFactory createCart 
			ownedBy: testObjectsFactory customer
			charging: testObjectsFactory notExpiredCreditCard 
			throught: self
			on: testObjectsFactory today
			registeringOn:  salesBook ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = Cashier cartCanNotBeEmptyErrorMessage.
			self assert: salesBook isEmpty ]! !!CashierTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/22/2013 12:22'!test05CashierChargesCreditCardUsingMerchantProcessor

	| cart cashier salesBook total creditCard debitedAmout debitedCreditCard  |

	cart := testObjectsFactory createCart.
	cart add: testObjectsFactory itemSellByTheStore.
	creditCard := testObjectsFactory notExpiredCreditCard.
	salesBook := OrderedCollection new.
 
	cashier:= Cashier 
		toCheckout: cart
		ownedBy: testObjectsFactory customer 
		charging: creditCard
		throught: self
		on: testObjectsFactory today
		registeringOn: salesBook.
		
	debitBehavior := [ :anAmount :aCreditCard | 
		debitedAmout := anAmount.
		debitedCreditCard := aCreditCard ].
	total := cashier checkOut total.
					
	self assert: debitedCreditCard = creditCard.
	self assert: debitedAmout = total.! !!CashierTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/22/2013 12:23'!test04CheckoutRegistersASale

	| cart cashier salesBook total |

	cart := testObjectsFactory createCart.
	cart add: testObjectsFactory itemSellByTheStore.
	salesBook := OrderedCollection new.
 
	cashier:= Cashier 
		toCheckout: cart 
		ownedBy: testObjectsFactory customer 
		charging: testObjectsFactory notExpiredCreditCard
		throught: self
		on: testObjectsFactory today
		registeringOn: salesBook.
		
	total := cashier checkOut total.
					
	self assert: salesBook size = 1.
	self assert: salesBook first total = total.! !!CashierTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/22/2013 12:01'!test03CanNotCheckoutWithAnExpiredCreditCart

	| cart salesBook |

	cart := testObjectsFactory createCart.
	cart add: testObjectsFactory itemSellByTheStore.
	salesBook := OrderedCollection new.
	
	self
		should: [ Cashier 
				toCheckout: cart 
				ownedBy: testObjectsFactory customer 
				charging: testObjectsFactory expiredCreditCard 
				throught: self
				on: testObjectsFactory today
				registeringOn: salesBook ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError | 
			self assert: anError messageText = Cashier canNotChargeAnExpiredCreditCardErrorMessage.
			self assert: salesBook isEmpty ]! !!CashierTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/22/2013 12:22'!test02CalculatedTotalIsCorrect

	| cart cashier |
	
	cart := testObjectsFactory createCart.
	cart add: 2 of: testObjectsFactory itemSellByTheStore.
	
	cashier :=  Cashier
		toCheckout: cart 
		ownedBy: testObjectsFactory customer
		charging: testObjectsFactory notExpiredCreditCard 
		throught: self
		on: testObjectsFactory today 
		registeringOn: OrderedCollection new.
		
	self assert: cashier checkOut total = (testObjectsFactory itemSellByTheStorePrice * 2)! !!CashierTest methodsFor: 'tests' stamp: 'HernanWilkinson 6/22/2013 12:02'!test06CashierDoesNotSaleWhenTheCreditCardHasNoCredit

	| cart cashier salesBook creditCard |

	cart := testObjectsFactory createCart.
	cart add: testObjectsFactory itemSellByTheStore.
	creditCard := testObjectsFactory notExpiredCreditCard.
	salesBook := OrderedCollection new.
 	debitBehavior := [ :anAmount :aCreditCard | self error: Cashier creditCardHasNoCreditErrorMessage].
	
	cashier:= Cashier 
		toCheckout: cart 
		ownedBy: testObjectsFactory customer
		charging: creditCard
		throught: self
		on: testObjectsFactory today
		registeringOn: salesBook.
		
	self 
		should: [cashier checkOut ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = Cashier creditCardHasNoCreditErrorMessage.
			self assert: salesBook isEmpty ]! !Clock subclass: #ManualClock	instanceVariableNames: 'now'	classVariableNames: ''	poolDictionaries: ''	category: 'TusLibros-Tests'!!ManualClock methodsFor: 'time change' stamp: 'HernanWilkinson 6/22/2013 12:54'!advanceTime: aDuration 
	
	now := now + aDuration ! !!ManualClock methodsFor: 'time change' stamp: 'HernanWilkinson 6/22/2013 13:08'!revertTime: aDuration 
	
	now := now + aDuration negated ! !!ManualClock methodsFor: 'time' stamp: 'HernanWilkinson 6/22/2013 12:56'!now
	
	^ now! !!ManualClock methodsFor: 'time' stamp: 'FernandoBalboa 11/26/2017 16:20'!today
	
	^now! !!ManualClock methodsFor: 'initialization' stamp: 'HernanWilkinson 6/22/2013 12:52'!initializeNow: aTime 

	now := aTime ! !"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!ManualClock class	instanceVariableNames: ''!!ManualClock class methodsFor: 'instance creation' stamp: 'HernanWilkinson 6/22/2013 12:52'!now: aTime 
	
	^self new initializeNow: aTime ! !Object subclass: #StoreTestObjectsFactory	instanceVariableNames: 'today'	classVariableNames: ''	poolDictionaries: ''	category: 'TusLibros-Tests'!!StoreTestObjectsFactory methodsFor: 'items' stamp: 'HernanWilkinson 6/22/2013 00:16'!anotherItemSellByTheStorePrice
	
	^15! !!StoreTestObjectsFactory methodsFor: 'items' stamp: 'HernanWilkinson 6/17/2013 18:08'!itemNotSellByTheStore
	
	^'invalidBook'! !!StoreTestObjectsFactory methodsFor: 'items' stamp: 'HernanWilkinson 6/17/2013 18:08'!itemSellByTheStorePrice
	
	^10! !!StoreTestObjectsFactory methodsFor: 'items' stamp: 'HernanWilkinson 6/22/2013 00:16'!anotherItemSellByTheStore
	
	^'anotherValidBook'! !!StoreTestObjectsFactory methodsFor: 'items' stamp: 'HernanWilkinson 6/17/2013 18:08'!itemSellByTheStore
	
	^ 'validBook'! !!StoreTestObjectsFactory methodsFor: 'credit card' stamp: 'HernanWilkinson 6/22/2013 11:24'!expiredCreditCard
	
	^CreditCard expiringOn: self expiredMonthOfYear ! !!StoreTestObjectsFactory methodsFor: 'credit card' stamp: 'FernandoBalboa 11/26/2017 16:18'!notExpiredMonthOfYear

	^ Month month: today monthIndex year: today year + 1! !!StoreTestObjectsFactory methodsFor: 'credit card' stamp: 'FernandoBalboa 11/26/2017 16:18'!expiredMonthOfYear 

	^ Month month: today monthIndex year: today year - 1! !!StoreTestObjectsFactory methodsFor: 'credit card' stamp: 'HernanWilkinson 6/22/2013 11:06'!notExpiredCreditCard
	
	^CreditCard expiringOn: self notExpiredMonthOfYear! !!StoreTestObjectsFactory methodsFor: 'customer' stamp: 'HernanWilkinson 6/22/2013 12:02'!customer
	
	^'aCustomer'! !!StoreTestObjectsFactory methodsFor: 'cart' stamp: 'HernanWilkinson 6/22/2013 00:16'!defaultCatalog
	
	^ Dictionary new
		at: self itemSellByTheStore put: self itemSellByTheStorePrice;
		at: self anotherItemSellByTheStore put: self anotherItemSellByTheStorePrice;
		yourself ! !!StoreTestObjectsFactory methodsFor: 'cart' stamp: 'HernanWilkinson 6/17/2013 18:08'!createCart
	
	^Cart acceptingItemsOf: self defaultCatalog! !!StoreTestObjectsFactory methodsFor: 'date' stamp: 'HernanWilkinson 6/17/2013 18:37'!today
	
	^ today! !!StoreTestObjectsFactory methodsFor: 'initialization' stamp: 'HernanWilkinson 6/17/2013 18:37'!initialize

	today := DateAndTime now! !TestCase subclass: #TusLibrosSystemFacadeTest	instanceVariableNames: 'testObjectsFactory clock systemFacade'	classVariableNames: ''	poolDictionaries: ''	category: 'TusLibros-Tests'!!TusLibrosSystemFacadeTest methodsFor: 'tests - add to cart ' stamp: 'HernanWilkinson 6/17/2015 20:53'!test05CanNotAddItemToNotCreatedCart

	self
		should: [systemFacade add: 1 of: self validBook toCartIdentifiedAs: self invalidCartId]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError | 
			self assert: anError messageText = systemFacade invalidCartIdErrorDescription ]
		! !!TusLibrosSystemFacadeTest methodsFor: 'tests - add to cart ' stamp: 'HernanWilkinson 6/17/2015 20:53'!test04CanAddItemsToACreatedCart

	| cartId |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	self
		shouldnt: [systemFacade add: 1 of: self validBook toCartIdentifiedAs: cartId]
		raise: Error - MessageNotUnderstood
		! !!TusLibrosSystemFacadeTest methodsFor: 'tests - add to cart ' stamp: 'HernanWilkinson 6/17/2015 20:53'!test17CanNotAddToCartWhenSessionIsExpired

	| cartId |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	self advanceTime: (systemFacade sessionDuration + 1 minutes) . 
	self 
		should: [systemFacade add: 2 of: self validBook toCartIdentifiedAs: cartId]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = systemFacade sessionHasExpiredErrorDescription ].

	self revertTime: systemFacade sessionDuration.
	self assert: (systemFacade listCartIdentifiedAs: cartId)	isEmpty
! !!TusLibrosSystemFacadeTest methodsFor: 'tests - add to cart ' stamp: 'HernanWilkinson 6/17/2015 20:53'!test06CanNotAddItemNotSellByTheStore

	| cartId |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	self
		should: [systemFacade add: 1 of: self invalidBook toCartIdentifiedAs: cartId ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError | 
			self assert: anError messageText = systemFacade invalidItemErrorMessage ]
		! !!TusLibrosSystemFacadeTest methodsFor: 'tests - checkout' stamp: 'HernanWilkinson 6/17/2015 20:53'!test19CanNotCheckOutCartWhenSessionIsExpired

	| cartId |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	systemFacade add: 2 of: self validBook toCartIdentifiedAs: cartId.
	self advanceTime: (systemFacade sessionDuration + 1 minutes) . 
	self 
		should: [systemFacade checkOutCartIdentifiedAs: cartId withCreditCardNumbered: '11' ownedBy: 'jp' expiringOn: testObjectsFactory notExpiredMonthOfYear ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = systemFacade sessionHasExpiredErrorDescription ].

	! !!TusLibrosSystemFacadeTest methodsFor: 'tests - checkout' stamp: 'HernanWilkinson 6/17/2015 20:53'!test13CanNotCheckoutWithAnExpiredCreditCard

	| cartId |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	systemFacade add: 1 of: self validBook toCartIdentifiedAs: cartId.
	self
		should: [systemFacade 
			checkOutCartIdentifiedAs: cartId 
			withCreditCardNumbered: '1111222233334444' 
			ownedBy: 'Juan Perez' 
			expiringOn: testObjectsFactory expiredMonthOfYear ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = systemFacade canNotChargeAnExpiredCreditCardErrorMessage ]
		
		! !!TusLibrosSystemFacadeTest methodsFor: 'tests - checkout' stamp: 'HernanWilkinson 6/17/2015 20:53'!test12CanNotCheckoutAnEmptyCart

	| cartId |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	self
		should: [systemFacade 
			checkOutCartIdentifiedAs: cartId 
			withCreditCardNumbered: '1111222233334444' 
			ownedBy: 'Juan Perez' 
			expiringOn: testObjectsFactory notExpiredMonthOfYear ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = systemFacade cartCanNotBeEmptyErrorMessage ]
		
		! !!TusLibrosSystemFacadeTest methodsFor: 'tests - checkout' stamp: 'HernanWilkinson 6/17/2015 20:53'!test11CanNotCheckoutANotCreatedCart

	self
		should: [systemFacade 
			checkOutCartIdentifiedAs: self invalidCartId  
			withCreditCardNumbered: '1111222233334444' 
			ownedBy: 'Juan Perez' 
			expiringOn: testObjectsFactory notExpiredMonthOfYear ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = systemFacade invalidCartIdErrorDescription ]
		
		! !!TusLibrosSystemFacadeTest methodsFor: 'tests - checkout' stamp: 'HernanWilkinson 6/17/2015 20:53'!test10CanCheckoutACart

	| cartId  |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	systemFacade add: 1 of: self validBook toCartIdentifiedAs: cartId.
	self
		shouldnt: [systemFacade 
			checkOutCartIdentifiedAs: cartId 
			withCreditCardNumbered: '1111222233334444' 
			ownedBy: 'Juan Perez' 
			expiringOn: testObjectsFactory notExpiredMonthOfYear ]
		raise: Error - MessageNotUnderstood
		
		! !!TusLibrosSystemFacadeTest methodsFor: 'time' stamp: 'HernanWilkinson 6/22/2013 12:53'!advanceTime: aDuration 
	
	clock advanceTime: aDuration ! !!TusLibrosSystemFacadeTest methodsFor: 'time' stamp: 'HernanWilkinson 6/22/2013 13:07'!revertTime: aDuration 
	
	clock revertTime: aDuration ! !!TusLibrosSystemFacadeTest methodsFor: 'tests - create cart' stamp: 'HernanWilkinson 6/17/2015 20:53'!test02CanNotCreateCartWithInvalidUser

	self
		should: [ systemFacade createCartFor: self invalidUser authenticatedWith: self validUserPassword ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError | 
			self assert: anError messageText = systemFacade invalidUserAndOrPasswordErrorDescription ]! !!TusLibrosSystemFacadeTest methodsFor: 'tests - create cart' stamp: 'HernanWilkinson 6/17/2015 20:53'!test03CanNotCreateCartWithInvalidPassword

	self
		should: [ systemFacade createCartFor: self validUser authenticatedWith: self invalidPassword ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError | 
			self assert: anError messageText = systemFacade invalidUserAndOrPasswordErrorDescription ]! !!TusLibrosSystemFacadeTest methodsFor: 'tests - create cart' stamp: 'HernanWilkinson 6/17/2015 20:53'!test01CanCreateCartWithValidUserAndPassword

	self 
		shouldnt: [systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword]
		raise: Error - MessageNotUnderstood ! !!TusLibrosSystemFacadeTest methodsFor: 'tests - list purchases' stamp: 'HernanWilkinson 6/17/2015 20:53'!test16CanNotListPurchasesOfValidCustomerWithInvalidPassword

	self 
		should: [systemFacade listPurchasesOf: self validUser authenticatingWith: self invalidPassword ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = systemFacade invalidUserAndOrPasswordErrorDescription ]! !!TusLibrosSystemFacadeTest methodsFor: 'tests - list purchases' stamp: 'HernanWilkinson 6/17/2015 20:53'!test14ListPurchasesIncludesBoughtItems

	| cartId purchases |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	systemFacade add: 2 of: self validBook toCartIdentifiedAs: cartId.
	systemFacade add: 1 of: self anotherValidBook toCartIdentifiedAs: cartId.
	systemFacade 
		checkOutCartIdentifiedAs: cartId 
		withCreditCardNumbered: '1111222233334444' 
		ownedBy: 'Juan Perez' 
		expiringOn: testObjectsFactory notExpiredMonthOfYear.
		
	purchases := systemFacade listPurchasesOf: self validUser authenticatingWith: self validUserPassword.

	self assert: (purchases at: self validBook) = (testObjectsFactory itemSellByTheStorePrice * 2).
	self assert: (purchases at: self anotherValidBook) = testObjectsFactory anotherItemSellByTheStorePrice.! !!TusLibrosSystemFacadeTest methodsFor: 'tests - list purchases' stamp: 'HernanWilkinson 6/17/2015 20:53'!test15CanNotListPurchasesOfInvalidCustomer

	self 
		should: [systemFacade listPurchasesOf: self invalidUser authenticatingWith: self validUserPassword ]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = systemFacade invalidUserAndOrPasswordErrorDescription ]! !!TusLibrosSystemFacadeTest methodsFor: 'tests - list cart' stamp: 'HernanWilkinson 6/17/2015 20:53'!test07ListCartOfAnEmptyCartReturnsAnEmptyBag

	| cartId |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	self assert: (systemFacade listCartIdentifiedAs: cartId) isEmpty 
	! !!TusLibrosSystemFacadeTest methodsFor: 'tests - list cart' stamp: 'HernanWilkinson 6/17/2015 20:53'!test09ListCartReturnsTheRightNumberOfItems

	| cartId cartContent |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	systemFacade add: 1 of: self validBook toCartIdentifiedAs: cartId.
	systemFacade add: 2 of: self anotherValidBook toCartIdentifiedAs: cartId.
	cartContent := systemFacade listCartIdentifiedAs: cartId.
	
	self assert: (cartContent occurrencesOf: self validBook) = 1. 
	self assert: (cartContent occurrencesOf: self anotherValidBook) = 2
! !!TusLibrosSystemFacadeTest methodsFor: 'tests - list cart' stamp: 'HernanWilkinson 6/17/2015 20:53'!test18CanNotListCartWhenSessionIsExpired

	| cartId |

	cartId := systemFacade createCartFor: self validUser authenticatedWith: self validUserPassword.
	self advanceTime: (systemFacade sessionDuration + 1 minutes) . 
	self 
		should: [systemFacade listCartIdentifiedAs: cartId]
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError |
			self assert: anError messageText = systemFacade sessionHasExpiredErrorDescription ].

! !!TusLibrosSystemFacadeTest methodsFor: 'tests - list cart' stamp: 'HernanWilkinson 6/17/2015 20:53'!test08CanNotListCartOfInvalidCartId

	self 
		should: [systemFacade listCartIdentifiedAs: self invalidCartId] 
		raise: Error - MessageNotUnderstood
		withExceptionDo: [ :anError | 
			self assert: anError messageText = systemFacade invalidCartIdErrorDescription ]
	! !!TusLibrosSystemFacadeTest methodsFor: 'merchant processor protocol' stamp: 'HernanWilkinson 6/22/2013 11:48'!debit: anAmount from: aCreditCard 
! !!TusLibrosSystemFacadeTest methodsFor: 'test objects' stamp: 'HernanWilkinson 6/21/2013 22:43'!validUsersAndPasswords
	
	^Dictionary new
		at: self validUser put: self validUserPassword;
		yourself! !!TusLibrosSystemFacadeTest methodsFor: 'test objects' stamp: 'HernanWilkinson 6/21/2013 22:30'!invalidUser

	^'invalidUser'! !!TusLibrosSystemFacadeTest methodsFor: 'test objects' stamp: 'HernanWilkinson 6/21/2013 22:28'!validUserPassword
	
	^'validUserPassword'! !!TusLibrosSystemFacadeTest methodsFor: 'test objects' stamp: 'HernanWilkinson 6/21/2013 22:27'!validUser
	
	^'validUser'! !!TusLibrosSystemFacadeTest methodsFor: 'test objects' stamp: 'HernanWilkinson 6/21/2013 23:06'!invalidPassword
	
	^'invalidPassword'! !!TusLibrosSystemFacadeTest methodsFor: 'test objects' stamp: 'HernanWilkinson 6/21/2013 23:50'!validBook
	
	^testObjectsFactory itemSellByTheStore ! !!TusLibrosSystemFacadeTest methodsFor: 'test objects' stamp: 'HernanWilkinson 6/22/2013 00:15'!anotherValidBook
	
	^testObjectsFactory anotherItemSellByTheStore ! !!TusLibrosSystemFacadeTest methodsFor: 'test objects' stamp: 'HernanWilkinson 6/21/2013 23:25'!invalidCartId
	
	"Devuelvo nil porque seguro que siempre sera un id invalido, no importa que sea el id - Hernan"
	^nil! !!TusLibrosSystemFacadeTest methodsFor: 'test objects' stamp: 'HernanWilkinson 6/21/2013 23:49'!invalidBook

	^testObjectsFactory itemNotSellByTheStore ! !!TusLibrosSystemFacadeTest methodsFor: 'setup' stamp: 'HernanWilkinson 6/22/2013 11:47'!merchantProcessor 

	^self! !!TusLibrosSystemFacadeTest methodsFor: 'setup' stamp: 'HernanWilkinson 6/17/2015 20:53'!setUp 

	testObjectsFactory := StoreTestObjectsFactory new.
	clock := ManualClock now: testObjectsFactory today.
	systemFacade := TusLibrosSystemFacade 
		authenticatingWith: self validUsersAndPasswords 
		acceptingItemsOf: testObjectsFactory defaultCatalog 
		registeringOn: self createSalesBook
		debitingThrought: self merchantProcessor 
		measuringTimeWith: clock
! !!TusLibrosSystemFacadeTest methodsFor: 'setup' stamp: 'HernanWilkinson 6/22/2013 11:42'!createSalesBook
	
	^OrderedCollection new! !