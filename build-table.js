let btnAdd = document.getElementById('addb');
let btnShow= document.getElementById('showb');
let btnDel= document.getElementById('delb');
let btnUpd= document.getElementById('updateb');
let table = document.querySelector('table');

let addNameInput = document.querySelector('#addnametxt');
let addAgeInput = document.querySelector('#addagetxt');
let addCountryInput = document.querySelector('#addcountrytxt');

let delUidInput = document.querySelector('#deluidtxt');

let updateUidInput = document.querySelector("#uidpersontoupdatetxt");
let updateNameInput = document.querySelector("#updatenametxt");
let updateAgeInput = document.querySelector("#updateagetxt");
let updateCountryInput = document.querySelector("#updatecountrytxt");

var Module = {
    onRuntimeInitialized: function() {
        var peopledb = new Module.PeopleDb();

        btnAdd.addEventListener('click', () => {
            let name = addNameInput.value;
            let age = addAgeInput.value;
            let country = addCountryInput.value;

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
                var personUid = peopledb.addPerson(name, age, country);
                console.log(name + ' has been added to the database. ' + name + '\'s UID is ' + personUid);
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
            var numPeople = peopledb.getDbSize();
            table.innerHTML = `<tr>
                                   <th>UID</th>
                                   <th>Name</th>
                                   <th>Age</th>
                                   <th>Country</th>
                               </tr>`;
            for (let i = 0; i < numPeople; i++)
            {
                let htmlRow =
                    `<tr>
                        <td>${peopledb.getPersonAtRowUid(i)}</td>
                        <td>${peopledb.getPersonAtRowName(i)}</td>
                        <td>${peopledb.getPersonAtRowAge(i)}</td>
                        <td>${peopledb.getPersonAtRowCountry(i)}</td>
                    </tr>`;

                table.innerHTML += htmlRow;
            }
        });

        delb.addEventListener('click', () => {
            let uid = delUidInput.value;
            if (uid == '')
            {
                alert('You need to enter an UID to delete a person');
            }
            else
            {
                var personToBeDeleted = peopledb.getPersonWithUid(uid);
                var deleted = peopledb.deletePersonWithUid(uid);
                if (deleted == 1)
                {
                    alert('Deleted ' + personToBeDeleted);
                }
                else
                {
                    alert('Could not find a person with a unique id of' + uid + ' in database. Try pressing \"Show\" to show all people with their UIDs');
                }
            }
        });

        updateb.addEventListener('click', () => {
            let uid = updateUidInput.value;
            if (uid == '')
            {
                alert('You need to enter an UID to delete a person');
            }
            else
            {
                var updatedName = updateNameInput.value;
                var updatedAge = updateAgeInput.value;
                var updatedCountry = updateCountryInput.value;
                var isPersonFoundAndUpdated = peopledb.updatePersonWithUid(uid, updatedName, updatedAge, updatedCountry);
                if (isPersonFoundAndUpdated == 1)
                {
                    alert('Updated person with uid ' + uid);
                }
                else
                {
                    alert('Could not find a person with a unique id of' + uid + ' in database. Try pressing \"Show\" to show all people with their UIDs');
                }
            }
        });
    }
};

// Compiled and ran like so:
// emcc -o table.html table.cpp --shell-file build-table.html -sNO_EXIT_RUNTIME=1 -sEXPORTED_FUNCTIONS=_addPerson -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --emrun
// emrun table.html