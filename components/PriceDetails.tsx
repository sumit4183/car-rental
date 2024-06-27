import React from 'react'

const PriceDetails = () => {
  return (
    <div className="bg-white p-6 rounded-lg shadow-lg w-full mt-10">
      <h2 className="text-2xl font-bold mb-4">PRICE DETAILS</h2>
      <div className="mb-4">
        <h3 className="text-lg font-bold mb-2">Rental charges</h3>
        <div className="flex justify-between mb-2">
          <span>4 Rental days x $51.51</span>
          <span>$206.05</span>
        </div>
        <div className="flex justify-between mb-2">
          <span>Connect Plus (GPS, data & calls)</span>
          <span>$87.96</span>
        </div>
        <div className="flex justify-between mb-2">
          <span>GPS</span>
          <span>$75.96</span>
        </div>
        <div className="flex justify-between mb-2">
          <span>Cover The Car</span>
          <span>$139.96</span>
        </div>
      </div>
      <div className="border-t border-gray-300 my-4"></div>
      <div className="mb-4">
        <h3 className="text-lg font-bold mb-2">Taxes and fees</h3>
        <div className="flex justify-between mb-2">
          <span>Rental Facility Charge</span>
          <span>$24.00</span>
        </div>
        <div className="flex justify-between mb-2">
          <span>Tire and Battery Fee</span>
          <span>$0.08</span>
        </div>
        <div className="flex justify-between mb-2">
          <span>Rental surcharge</span>
          <span>$8.00</span>
        </div>
        <div className="flex justify-between mb-2">
          <span>Vehicle License Fee</span>
          <span>$3.60</span>
        </div>
        <div className="flex justify-between mb-2">
          <span>Privilege Fee Recovery Charge</span>
          <span>$51.36</span>
        </div>
        <div className="flex justify-between mb-2">
          <span>Taxes</span>
          <span>$29.71</span>
        </div>
      </div>
      <div className="border-t border-gray-300 my-4"></div>
      <div className="flex justify-between text-xl font-bold">
        <span>Total (incl. tax)</span>
        <span>$626.68</span>
      </div>
    </div>
  )
}

export default PriceDetails