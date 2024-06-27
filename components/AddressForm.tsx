import React from 'react'

const AddressForm = () => {
  return (
    <div className="bg-white p-6 rounded-lg shadow-lg w-full mt-10">
      <h2 className="text-2xl font-bold mb-4">What is your invoice address?</h2>
      <form>
        <div className="mb-4">
          <label htmlFor="country" className="block text-sm font-bold mb-2">
            Country
          </label>
          <div className="relative">
            <select
              id="country"
              className="w-full p-3 border rounded appearance-none"
              style={{ backgroundImage: 'url(/images/usa-flag.png)' }}
            >
              <option value="USA">United States</option>
              {/* Add more options as needed */}
            </select>
            <div className="pointer-events-none absolute inset-y-0 right-0 flex items-center px-2 text-gray-700">
              <svg className="fill-current h-4 w-4" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20"><path d="M5.516 6.516l4.484 4.484 4.484-4.484-1.032-1.032-3.452 3.452-3.452-3.452z"/></svg>
            </div>
          </div>
        </div>
        <div className="mb-4">
          <label htmlFor="streetAddress" className="block text-sm font-bold mb-2">
            Street address
          </label>
          <input
            type="text"
            id="streetAddress"
            className="w-full p-3 border rounded"
          />
        </div>
        <div className="flex justify-between mb-4">
          <div className="w-1/2 mr-2">
            <label htmlFor="zip" className="block text-sm font-bold mb-2">
              Zip
            </label>
            <input
              type="text"
              id="zip"
              className="w-full p-3 border rounded"
            />
          </div>
          <div className="w-1/2 ml-2">
            <label htmlFor="city" className="block text-sm font-bold mb-2">
              City
            </label>
            <input
              type="text"
              id="city"
              className="w-full p-3 border rounded"
            />
          </div>
        </div>
        <div className="mb-4">
          <label htmlFor="state" className="block text-sm font-bold mb-2">
            State
          </label>
          <input
            type="text"
            id="state"
            className="w-full p-3 border rounded"
          />
        </div>
      </form>
    </div>
  )
}

export default AddressForm