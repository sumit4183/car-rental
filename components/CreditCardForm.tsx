import React from 'react'

const CreditCardForm = () => {
  return (
    <div className="bg-white p-6 rounded-lg shadow-lg w-full mt-10">
      <h2 className="text-2xl font-bold mb-4">What credit card would you like to pay with?</h2>
      <form>
        <div className="mb-4">
          <label htmlFor="cardNumber" className="block text-sm font-bold mb-2">
            Card number
          </label>
          <input
            type="text"
            id="cardNumber"
            className="w-full p-3 border rounded"
            placeholder="1234 1234 1234 1234"
          />
        </div>
        <div className="mb-4">
          <label htmlFor="cardholderName" className="block text-sm font-bold mb-2">
            Cardholder name
          </label>
          <input
            type="text"
            id="cardholderName"
            className="w-full p-3 border rounded"
          />
        </div>
        <div className="flex justify-between mb-4">
          <div className="w-1/2 mr-2">
            <label htmlFor="expirationDate" className="block text-sm font-bold mb-2">
              Expiration date
            </label>
            <input
              type="text"
              id="expirationDate"
              className="w-full p-3 border rounded"
              placeholder="MM/YY"
            />
          </div>
          <div className="w-1/2 ml-2">
            <label htmlFor="cvv" className="block text-sm font-bold mb-2">
              CVV
            </label>
            <input
              type="text"
              id="cvv"
              className="w-full p-3 border rounded"
              placeholder="123"
            />
          </div>
        </div>
        <div className="mb-4 flex items-center">
          <img src="/images/amex.png" alt="Amex" className="h-8 mr-2" />
          <img src="/images/discover.png" alt="Discover" className="h-8 mr-2" />
          <img src="/images/mastercard.png" alt="MasterCard" className="h-8 mr-2" />
          <img src="/images/visa.png" alt="Visa" className="h-8" />
        </div>
        <div className="text-sm text-gray-600">
          <p>If using a credit card, it must be issued in the drivers name. If using a debit card, <a href="#" className="text-blue-600 underline">additional documentation</a> will need to be shown at pickup. Debit cards are not accepted for local renters at this branch. The total amount will be charged in USD (with the exchange rate valid at the time of debit).</p>
        </div>
      </form>
    </div>
  )
}

export default CreditCardForm