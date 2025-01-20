<template>
  <div class="windows">
    <div class="globalHeader">
      <h1>Windows</h1>
    </div>
    <div class="container">
      <div class="boxHeader">
        <div class="boxHeaderTexts">
          <p>Window #</p>
          <p>Current Staff</p>
          <p></p>
          <p></p>
        </div>
      </div>
      <div class="windowBoxes">
        <div class="windowBox" v-for="(item, index) in windowCount" :key="index">
          <p>{{ item.windowNumber }}</p>
          <p>{{ item.staff }}</p>
          <div class="statusBox">
            <button class="statusButton" @click.stop="editWindowModal(index)">
              Edit Window
            </button>
          </div>
          <div class="statusBox">
            <button class="statusButton" @click.stop="viewLogs(index)">
              View Logs
            </button>
          </div>
        </div>
      </div>
      <div class="boxHeader" @click="showAddWindowModal">
        <div class="boxHeaderTexts">
          <p id="newAccText">+ Add New Window</p>
        </div>
      </div>

      <!-- Add Window Modal -->
      <div v-if="showAddModal" class="modal-box" style="padding: 1">
        <div style="display: flex; flex-direction: column">
          <div class="modalHeader" style="display: flex; padding: 0.5rem">
            <span style="font-size: 1rem; font-weight: 600">Add New Window</span>
            <img :src="x" alt="x" style="margin-left: auto; cursor: pointer" @click="closeModal" />
          </div>
          <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
          <div class="modalBody">
            <div class="modalBoxFormTitle">
              Enter new staff name
            </div>
            <div class="input-group mb-3">
              <input type="text" class="form-control" placeholder="Staff Name" aria-label="Staff Name"
                aria-describedby="basic-addon1" v-model="newStaff" />
            </div>
          </div>
          <div class="modalBody">
            <div class="modalBoxFormTitle">
              Enter a window number
            </div>
            <div class="input-group mb-3">
              <input type="text" class="form-control" placeholder="Window Number" aria-label="Window Number"
                aria-describedby="basic-addon1" v-model="windowNumber" />
            </div>
          </div>
          <div class="modalBody">
            <div class="modalBoxFormTitle">
              Enter a new email address
            </div>
            <div class="input-group mb-3">
              <input type="text" class="form-control" placeholder="Email" aria-label="Email"
                aria-describedby="basic-addon1" v-model="email" />
            </div>
          </div>
          <div class="modalBody">
            <div class="modalBoxFormTitle">
              Enter password
            </div>
            <div class="input-group mb-3">
              <input type="password" class="form-control" placeholder="Password" aria-label="Password"
                aria-describedby="basic-addon1" v-model="password" />
            </div>
          </div>
          <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
          <div class="modalFooter" style="
              display: flex;
              margin-left: auto;
              gap: 0.5rem;
              padding: 0 0.5rem 0.5rem 0.5rem;
            ">
            <button type="button" class="btn btn-secondary" @click="closeModal">
              Cancel
            </button>
            <button type="button" class="btn btn-primary specbtn" style="border: none; background-color: #031633"
              @click="addWindow">
              Add Window
            </button>
          </div>
        </div>
      </div>

      <div v-if="editWindow" class="modal-box" style="padding: 0">
        <div style="display: flex; flex-direction: column">
          <div class="modalHeader" style="display: flex; padding: 1rem">
            <span style="font-size: 1rem; font-weight: 600">Edit Window</span>
            <img :src="x" alt="x" style="margin-left: auto; cursor: pointer" @click="closeModal" />
          </div>
          <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
          <div class="modalBody" style="padding: 1rem">
            <div class="modalBoxFormTitle">
              Current Staff
            </div>
            <div class="input-group mb-3">
              <input type="text" class="form-control" placeholder="Staff Name" aria-label="Staff Name"
                aria-describedby="basic-addon1" v-model="staff" />
            </div>
            <div class="modalBody" style="padding: 0rem">
              <div class="modalBoxFormTitle">
                Window #
              </div>
              <div class="input-group mb-3">
                <input type="text" class="form-control" placeholder="Window Number" aria-label="Window Number"
                  aria-describedby="basic-addon1" v-model="windowNumber" />
              </div>
            </div>
            <button class="delete-button" @click="deleteWindowModal()">
              Delete Window
            </button>
          </div>
          <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
          <div class="modalFooter" style="
              display: flex;
              margin-left: auto;
              gap: 0.5rem;
              padding: 0 1rem 1rem 1rem;
            ">
            <button type="button" class="btn btn-secondary" @click="closeModal">
              Cancel
            </button>
            <button type="button" class="btn btn-primary specbtn" style="border: none; background-color: #031633"
              @click="saveChanges">
              Confirm
            </button>
          </div>
        </div>
      </div>

      <!-- View Logs Modal -->
      <div v-if="showLogModal" class="modal-box">
        <div style="display: flex; flex-direction: column">
          <div class="modalHeader" style="display: flex; padding: 1rem">
            <span style="font-size: 1rem; font-weight: 600">Staff Logs</span>
            <img :src="x" alt="x" style="margin-left: auto; cursor: pointer" @click="closeModal" />
          </div>
          <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
          <div class="modalBody" style="padding: 1rem; max-height: 300px; overflow-y: auto">
            <table style="width: 100%; border-collapse: collapse; text-align: left">
              <thead>
                <tr style="border-bottom: 1px solid #ced4da">
                  <th style="padding: 0.5rem">Staff</th>
                  <th style="padding: 0.5rem">Start</th>
                  <th style="padding: 0.5rem">End</th>
                  <th style="padding: 0.5rem">Date</th>
                </tr>
              </thead>
              <tbody>
                <tr v-for="log in selectedLogs" :key="log.id" style="border-bottom: 1px solid #ced4da">
                  <td style="padding: 0.5rem">{{ log.staff }}</td>
                  <td style="padding: 0.5rem">{{ log.start }}</td>
                  <td style="padding: 0.5rem">{{ log.end }}</td>
                  <td style="padding: 0.5rem">{{ log.date }}</td>
                </tr>
              </tbody>
            </table>
          </div>
          <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
          <div class="modalFooter" style="display: flex; justify-content: flex-end; padding: 1rem">
            <button type="button" class="btn btn-secondary" @click="closeModal">
              Close
            </button>
          </div>
        </div>
      </div>

      <div v-if="blur" class="overlay" @click="closeModal"></div>
      <div v-if="deleteModalBox" class="deleteModalBox">
        <div class="deleteModalHeader">
          <span>Confirm Ticket Completion</span>
          <img :src="x" alt="close" @click="closeModal" style="cursor: pointer" />
        </div>
        <div class="line"></div>
        <div class="deleteModalBody">
          <p>
            Are you sure you want to delete this window? This action
            cannot be undone and any unsaved changes or progress will be lost.
          </p>
        </div>
        <div class="line"></div>
        <div class="deleteModalFooter">
          <button @click="closeModal" class="btn btn-secondary">Cancel</button>
          <button @click="deleteWindow" class="btn btn-primary specbtn">
            Confirm
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import x from "@/assets/x-lg.svg";
import { supabase } from "@/client/supabase";

export default {
  name: "windows",
  data() {
    return {
      x,
      windowCount: [],
      editWindow: false,
      showLogModal: false,
      showAddModal: false,
      deleteModalBox: false,
      blur: false,
      staff: "",
      newStaff: "",
      email: "",
      password: "",
      windowNumber: null,
      editingIndex: null,
      selectedLogs: [],
    };
  },
  mounted() {
    this.getWindows();
  },
  methods: {
    closeModal() {
      this.deleteModalBox = false;
      this.showAddModal = false;
      this.showLogModal = false;
      this.editWindow = false;
      this.blur = false;
      this.selectedLogs = [];
      this.windowNumber = null;
      this.email = "";
      this.password = "";
      this.staff = "";
      this.newStaff = "";
    },
    showAddWindowModal() {
      this.blur = true;
      this.showAddModal = true;
    },
    async addWindow() {

      const newWindow = {
        window_number: this.windowNumber,
        current_staff: this.newStaff,
      };
      const { data: staffName } = await supabase
        .from("users")
        .select("display_name")
        .eq("display_name", this.newStaff);

      if (staffName.length === 0) {
        alert("Staff not found");
        return;
      }
      if (!this.windowNumber) {
        alert("Please enter a window number.");
        return;
      }
      if (isNaN(this.windowNumber)) {
        alert("Please enter a valid window number.");
        return;
      }
      const { data: windowNumber } = await supabase
        .from("windows")
        .select("window_number")
        .eq("window_number", this.windowNumber);

      const { data: windowStaff } = await supabase
        .from("users")
        .select("email")
        .eq("email", this.email);

      if (windowStaff.length !== 0) {
        alert("Staff already exists.");
        return;
      }
      if (windowNumber.length !== 0) {
        alert("Window number already exists.");
        return;
      }
      const { data, error } = await supabase
        .from("windows")
        .insert(newWindow);
      if (error) {
        console.error("Error adding window:", error.message);
        alert("Error adding window.");
        return;
      }
      const { user, error: signUpError } =
        await supabase.auth.admin.createUser({
          email: this.email,
          password: this.password,
        });
      if (signUpError) {
        alert("Unable to create user.");
      } else {
        console.log("User created successfully!");
      }
      const { error: addAccountError } = await supabase.from("users").insert({
        email: this.email,
        display_name: this.newStaff,
        window_number: this.windowNumber,
      });
      this.windowCount.push({
        staff: this.newStaff,
        windowNumber: this.windowNumber,
      });
      this.closeModal();
      alert("Window added successfully.");
    },
    async getWindows() {
      const { data, error } = await supabase
        .from("windows")
        .select("window_number, current_staff");
      if (error) {
        console.error(error);
        return;
      }
      const sortedData = data.sort(
        (a, b) => a.window_number - b.window_number
      );
      this.windowCount = sortedData.map((item) => ({
        windowNumber: item.window_number,
        staff: item.current_staff,
      }));
    },
    async viewLogs(index) {
      this.blur = true;
      this.showLogModal = true;
      const { data, error } = await supabase
        .from("staff_logs")
        .select("*")
        .eq("window_number", index + 1);
      if (error) {
        console.error("Error fetching logs:", error.message);
        return;
      }
      this.selectedLogs = data || [];
    },
    editWindowModal(index) {
      this.blur = true;
      this.editWindow = true;
      this.editingIndex = index;
      this.staff = this.windowCount[index].staff;
      this.windowNumber = this.windowCount[index].windowNumber;
    },
    async deleteWindow() {
      const { error } = await supabase
        .from("windows")
        .delete()
        .eq("window_number", this.editingIndex + 1);
      if (error) {
        console.error("Error deleting window:", error.message);
        alert("Error deleting window.");
        return;
      }
      this.windowCount.splice(this.editingIndex, 1);
      this.closeModal();
      alert("Window deleted successfully.");
    },
    async saveChanges() {
      const { data } = await supabase
        .from("users")
        .select("display_name")
        .eq("display_name", this.staff);

      if (data.length === 0) {
        alert("Staff not found");
        return;
      }
      if (isNaN(this.windowNumber)) {
        alert("Please enter a valid window number.");
        return;
      }
      const { error } = await supabase
        .from("windows")
        .update({ current_staff: this.staff })
        .eq("window_number", this.editingIndex + 1);
      if (error) {
        console.error("Error updating window:", error.message);
        alert("Error updating window.");
        return;
      }
      this.windowCount[this.editingIndex].staff = this.staff;
      this.closeModal();
      alert("Changes saved successfully.");
    },
    deleteWindowModal() {
      this.editWindow = false;
      this.deleteModalBox = true;
      this.blur = true;
    },
  },
};
</script>

<style scoped>
.windows {
  background: #e9ecef;
  height: 100vh;
}

.container {
  display: flex;
  flex-direction: column;
  align-items: center;
  padding: 2rem;
  gap: 0;
}

.boxHeader {
  width: 69.5625rem;
  height: 3.0625rem;
  background: #031633;
  display: flex;
  align-items: center;
  justify-content: space-between;
  box-sizing: border-box;
}

.boxHeaderTexts,
.windowBox {
  display: flex;
  align-items: center;
  width: 100%;
  padding: 0 1rem;
  gap: 1rem;
  box-sizing: border-box;
}

.boxHeaderTexts p,
.windowBox p {
  margin: 0;
  text-align: center;
  overflow: hidden;
  white-space: nowrap;
  text-overflow: ellipsis;
  flex: 1;
}

.boxHeaderTexts p {
  color: white;
  font-weight: 800;
}

.windowBox p {
  color: #152536;
}

.boxHeaderTexts p:nth-child(1),
.windowBox p:nth-child(1) {
  flex: 2;
}

.boxHeaderTexts p:nth-child(2),
.windowBox p:nth-child(2) {
  flex: 2;
  text-align: left;
}

.boxHeaderTexts p:nth-child(3),
.windowBox p:nth-child(3) {
  flex: 2;
}

.boxHeaderTexts p:nth-child(4),
.windowBox .statusBox {
  flex: 2;
  display: flex;
  align-items: center;
  justify-content: center;
}

.boxHeaderTexts p:nth-child(5),
.windowBox .statusBox:nth-child(5) {
  flex: 2;
  display: flex;
  align-items: center;
  justify-content: center;
}

.windowBox {
  width: 69.5625rem;
  height: 3.0625rem;
  background: #ffffff;
  border-bottom: 1px solid #dee2e6;
  display: flex;
  align-items: center;
  padding: 0 1rem;
  box-sizing: border-box;
}

.dropdown {
  position: relative;
}

.dropdown-menu {
  position: absolute;
  top: 100%;
  left: 0;
  background-color: white;
  border: 1px solid #dee2e6;
  border-radius: 5px;
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
  z-index: 1050;
  display: block;
}

.dropdown-item {
  padding: 0.5rem 1rem;
  cursor: pointer;
  text-align: left;
}

.dropdown-item:hover {
  background-color: #f8f9fa;
}

.overlay {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background: rgba(0, 0, 0, 0.5);
  backdrop-filter: blur(10px);
}

.modal-box {
  position: fixed;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  padding: 20px;
  background-color: white;
  border-radius: 10px;
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
  z-index: 1000;
  width: 38.9375rem;
  text-align: center;
}

.modal-box button {
  margin-top: 20px;
  padding: 10px 20px;
}

.modalBoxFormTitle {
  font-weight: 800;
  display: flex;
  padding: 5px
}

.statusButton {
  width: 100%;
  height: 100%;
  background: none;
  border: none;
  font-size: 0.875rem;
  cursor: pointer;
  color: #031633;
  font-weight: 600;
}

.statusBox {
  position: relative;
  overflow: visible;
  width: 9.8675rem;
  height: 2rem;
  background-color: #cfe2ff;
  border-radius: 10px;
  display: flex;
  align-items: center;
  justify-content: center;
}

#newAccText {
  cursor: pointer;
}

.delete-button {
  background: #ffffff;
  border: 1px solid #dc3545;
  color: #dc3545;
  border-radius: 5px;
  padding: 0.5rem 1rem;
  cursor: pointer;
  width: 100%;
  text-align: center;
}

.delete-button:hover {
  background: #ffcccc;
}

.deleteModalBox {
  position: fixed;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  background: white;
  padding: 2rem;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
  border-radius: 8px;
  z-index: 1000;
}

.deleteModalHeader {
  display: flex;
  justify-content: space-between;
  font-weight: bold;
  margin-bottom: 1rem;
}

.deleteModalBody {
  padding: 10px;
}

.deleteModalFooter {
  display: flex;
  justify-content: flex-end;
  gap: 1rem;
  padding: 20px;
}

.line {
  width: 100%;
  height: 1px;
  background: #ced4da;
}
</style>
