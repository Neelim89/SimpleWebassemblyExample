let btnAdd = document.getElementById('addb');
let btnShow= document.getElementById('showb');
let table = document.querySelector('table');

let nameInput = document.querySelector('#name');
let ageInput = document.querySelector('#age');
let countryInput = document.querySelector('#country');

var Module = {
    onRuntimeInitialized: function() {
        var peopledb = new Module.PeopleDb();

        btnAdd.addEventListener('click', () => {
            let name = nameInput.value;
            let age = ageInput.value;
            let country = countryInput.value;

            if (name == '' || age == '' || country == '')
            {
                if (name == '')
                {
                    alert('Please enter in a name');
                }
                if (age == '')
                {
                    alert('Please enter in an age');
                }
                if (country == '')
                {
                    alert('Please enter in a country');
                }
            }
            else
            {
                peopledb.addPerson(name, age, country);
                console.log(peopledb.getPersonAtRow(0));
            }
            // let template =
            //             `<tr>
            //                 <td>${name}</td>
            //                 <td>${age}</td>
            //                 <td>${country}</td>
            //             </tr>`;

            // table.innerHTML += template;
        });

        btnShow.addEventListener('click', () => {
            numPeople = peopledb.getDbSize();
            table.innerHTML = `<tr>
                                   <th>Name</th>
                                   <th>Age</th>
                                   <th>Country</th>
                               </tr>`;
            for (let i = 0; i < numPeople; i++)
            {
                let htmlRow =
                    `<tr>
                        <td>${peopledb.getPersonAtRowName(i)}</td>
                        <td>${peopledb.getPersonAtRowAge(i)}</td>
                        <td>${peopledb.getPersonAtRowCountry(i)}</td>
                    </tr>`;

                table.innerHTML += htmlRow;
            }
        });
    }
};

// Compiled and ran like so:
// emcc -o table.html table.cpp --shell-file build-table.html -sNO_EXIT_RUNTIME=1 -sEXPORTED_FUNCTIONS=_addPerson -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --emrun
// emrun table.html