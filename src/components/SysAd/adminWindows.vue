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
        <div
          class="windowBox"
          v-for="(item, index) in windowCount"
          :key="index"
        >
          <p>{{ index + 1 }}</p>
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
      <div class="boxHeader" @click="addWindow">
        <div class="boxHeaderTexts">
          <p id="newAccText">+ Add New Window</p>
        </div>
      </div>
      <div v-if="blur" class="overlay" @click="closeModal"></div>
      <div v-if="editWindow" class="modal-box" style="padding: 0">
        <div style="display: flex; flex-direction: column">
          <div class="modalHeader" style="display: flex; padding: 1rem">
            <span style="font-size: 1rem; font-weight: 600">Edit Window</span>
            <img
              :src="x"
              alt="x"
              style="margin-left: auto; cursor: pointer"
              @click="closeModal"
            />
          </div>
          <div
            style="height: 1px; width: 100%; background-color: #ced4da"
          ></div>
          <div class="modalBody" style="padding: 1rem">
            <div class="input-group mb-3">
              <input
                type="staff"
                class="form-control"
                placeholder="Staff Name"
                aria-label="Email Address"
                aria-describedby="basic-addon1"
                v-model="staff"
              />
            </div>
            <button class="delete-button" @click="deleteWindow">
              Delete Window
            </button>
          </div>
          <div
            style="height: 1px; width: 100%; background-color: #ced4da"
          ></div>
          <div
            class="modalFooter"
            style="
              display: flex;
              margin-left: auto;
              gap: 0.5rem;
              padding: 0 1rem 1rem 1rem;
            "
          >
            <button type="button" class="btn btn-secondary" @click="closeModal">
              Cancel
            </button>
            <button
              type="button"
              class="btn btn-primary specbtn"
              style="border: none; background-color: #031633"
              @click="saveChanges(editingIndex)"
            >
              confirm
            </button>
          </div>
        </div>
      </div>
      <div v-if="showLogModal" class="modal-box" style="padding: 0">
        <div style="display: flex; flex-direction: column">
          <div class="modalHeader" style="display: flex; padding: 1rem">
            <span style="font-size: 1rem; font-weight: 600">View Logs</span>
            <img
              :src="x"
              alt="x"
              style="margin-left: auto; cursor: pointer"
              @click="closeModal"
            />
          </div>
          <div
            style="height: 1px; width: 100%; background-color: #ced4da"
          ></div>
          <div class="modalBody" style="padding: 1rem">
            <table
              style="width: 100%; border-collapse: collapse; text-align: left"
            >
              <thead>
                <tr style="border-bottom: 1px solid #ced4da">
                  <th style="padding: 0.5rem">Staff</th>
                  <th style="padding: 0.5rem">Start</th>
                  <th style="padding: 0.5rem">End</th>
                  <th style="padding: 0.5rem">Date</th>
                </tr>
              </thead>
              <tbody>
                <tr
                  v-for="log in selectedLogs"
                  :key="log.id"
                  style="border-bottom: 1px solid #ced4da"
                >
                  <td style="padding: 0.5rem">{{ log.staff }}</td>
                  <td style="padding: 0.5rem">{{ log.start }}</td>
                  <td style="padding: 0.5rem">{{ log.end }}</td>
                  <td style="padding: 0.5rem">{{ log.date }}</td>
                </tr>
              </tbody>
            </table>
          </div>

          <div
            style="height: 1px; width: 100%; background-color: #ced4da"
          ></div>
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
        blur: false,
        staff: "",
        editingIndex: null,
        selectedLogs: [],
      };
    },
    mounted() {
      this.getWindows();
    },
    methods: {
      closeModal() {
        this.showModal = false;
        this.editWindow = false;
        this.showLogModal = false;
        this.blur = false;
        this.selectedLogs = [];
      },
      editWindowModal(index) {
        this.blur = true;
        this.editWindow = true;
        this.editingIndex = index;
        const window = this.windowCount[index];
        this.oldStaff = window.staff;
        this.staff = window.staff;
      },
      async deleteWindow() {
        if (this.editingIndex !== null) {
          const windowToDelete = this.windowCount[this.editingIndex];

          try {
            const { error } = await supabase
              .from("windows")
              .delete()
              .eq("current_staff", windowToDelete.staff);

            if (error) {
              console.error("Error deleting service:", error);
              return;
            }

            this.windowCount.splice(this.editingIndex, 1);
            console.log("Service deleted successfully");

            this.closeModal();
          } catch (err) {
            console.error("Unexpected error deleting service:", err);
          }
        }
      },
      async viewLogs(index) {
        this.blur = true;
        this.showLogModal = true;
        this.selectedLogs = [];
        const { data, error } = await supabase
          .from("staff_logs")
          .select("staff, start, end, date")
          .eq("window_number", "Window 1");

        if (data) {
          this.selectedLogs = data;
        }
      },
      async getWindows() {
        const { data, error } = await supabase
          .from("windows")
          .select("window_number, current_staff");

        if (error) {
          console.error(error);
        }

        if (data) {
          const sortedData = data.sort(
            (a, b) => a.window_number - b.window_number
          );
          this.windowCount = sortedData.map((item) => ({
            staff: item.current_staff,
          }));
        }
      },
      async addWindow() {
        this.windowCount.push({
          staff: this.staff,
        });
        this.closeModal();
      },
      async saveChanges() {
        if (this.editingIndex !== null) {
          const updatedWindow = {
            staff: this.staff,
          };
          const { data: staff, error: staffError } = await supabase
            .from("users")
            .select("display_name")
            .eq("display_name", this.staff);

          if (staff.length === 0) {
            alert("Staff does not exist");
            return;
          }
          this.windowCount[this.editingIndex] = updatedWindow;
          const { data, error } = await supabase
            .from("windows")
            .update({ current_staff: this.staff })
            .eq("current_staff", this.oldStaff);
        }
        console.log(this.oldStaff);
        this.closeModal();
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
    background-color: #ebe5fc;
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
</style>
