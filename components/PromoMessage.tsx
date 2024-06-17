import React from 'react'

const PromoMessage = () => {
  return (
    <div className="bg-gray-100 p-6 shadow-md rounded-md mt-8 flex mx-auto justify-between items-center w-10/12">
      <div>
        <h3 className="text-2xl font-bold mb-2">WANT A DISCOUNT? SIGN-UP AND GET GREAT DEALS ON CAR RENTAL!</h3>
        <p className="text-lg">Join & Save. Receive our newest and best rental car deals. Enroll today!</p>
      </div>
      <button className="bg-yellow-500 text-white py-3 px-6 rounded-md text-lg font-semibold">
        SIGN UP NOW
      </button>
    </div>
  )
}

export default PromoMessage