import React from 'react'

const FilterSidebar = () => {
  return (
    <div className="w-1/4 pr-4">
      <div className="bg-white rounded-2xl border-gray-300 border">
        <h3 className="font-bold m-4 text-xl">Filters</h3>
        <hr className="border-gray-300" />
        <div className="filter-bar-section">
          <h4 className="font-bold">Mileage</h4>
          <div>
            <label>
              <input type="checkbox" /> Unlimited Mileage
            </label>
            <span className="float-right">$141</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> Limited Mileage
            </label>
            <span className="float-right">$174</span>
          </div>
        </div>
        <hr className="border-gray-300" />
        <div className="filter-bar-section">
          <h4 className="font-bold">Vehicle Type</h4>
          <div>
            <label>
              <input type="checkbox" /> Cars
            </label>
            <span className="float-right">$141</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> Trucks
            </label>
            <span className="float-right">$153</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> SUVs
            </label>
            <span className="float-right">$159</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> Vans
            </label>
            <span className="float-right">$217</span>
          </div>
        </div>
        <hr className="border-gray-300" />
        <div className="filter-bar-section">
          <h4 className="font-bold">Fuel Type</h4>
          <div>
            <label>
              <input type="checkbox" /> Gasoline Vehicle
            </label>
            <span className="float-right">$141</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> Electric Vehicle
            </label>
            <span className="float-right">$155</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> Hybrid Vehicle
            </label>
            <span className="float-right">-</span>
          </div>
        </div>
        <hr className="border-gray-300" />
        <div className="filter-bar-section rounded-ee-2xl rounded-bl-2xl">
          <h4 className="font-bold">Number of Passengers</h4>
          <div>
            <label>
              <input type="checkbox" /> 2+
            </label>
            <span className="float-right">$141</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> 4+
            </label>
            <span className="float-right">$141</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> 5+
            </label>
            <span className="float-right">$141</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> 7+
            </label>
            <span className="float-right">$187</span>
          </div>
          <div>
            <label>
              <input type="checkbox" /> 8+
            </label>
            <span className="float-right">$220</span>
          </div>
        </div>
      </div>
    </div>
  )
}

export default FilterSidebar