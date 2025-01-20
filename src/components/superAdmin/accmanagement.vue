<template>
  <div class="accmanagement">
    <div class="globalHeader">
      <h1>Accounts</h1>
    </div>
    <div class="container">
      <div class="boxHeader">
        <div class="boxHeaderTexts">
          <p>#</p>
          <p>Email</p>
          <p>Role</p>
          <p></p>
        </div>
      </div>
      <div class="ticketBoxes">
        <div
          class="ticketBox"
          v-for="(item, index) in accountCount"
          :key="index"
        >
          <p>{{ index + 1 }}</p>
          <p>{{ item.email }}</p>
          <p>{{ item.role }}</p>
          <div class="statusBox">
            <button class="statusButton" @click.stop="editAccount(index)">
              Edit account
            </button>
          </div>
        </div>
      </div>
      <div class="newAccount" @click="addAccountModal">
        <div class="newAccountTexts">
          <p>+ Add New Account</p>
        </div>
      </div>
      <div v-if="blur" class="overlay" @click="closeModal"></div>
      <div v-if="showModal" class="modal-box" style="padding: 0">
        <div style="display: flex; flex-direction: column">
          <div class="modalHeader" style="display: flex; padding: 1rem">
            <span style="font-size: 1rem; font-weight: 600">Add Account</span>
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
            <div class="modalBoxFormTitle">
            Enter New Email Address:
            </div>
            <div class="input-group mb-3">
              <input
                type="email"
                class="form-control"
                placeholder="Email Address"
                aria-label="Email Address"
                aria-describedby="basic-addon1"
                v-model="email"
              />
            </div>
            <div class="modalBoxFormTitle">
            Select a role:
            </div>
            <div class="input-group mb-3">
              <div class="dropdown">
                <input
                  type="button"
                  class="form-control"
                  :value="role || 'Select Role'"
                  @click="toggleRoleDropdown"
                />
                <div v-if="showRoleDropdown" class="dropdown-menu" @click.stop>
                  <p
                    v-for="roleOption in ['staff', 'system admin']"
                    :key="roleOption"
                    @click="selectRole(roleOption)"
                    class="dropdown-item"
                  >
                    {{ roleOption }}
                  </p>
                </div>
              </div>
            </div>
            <div class="modalBoxFormTitle">
            Enter a new password:
            </div>
            <div class="input-group mb-3">
              <input
                type="password"
                class="form-control"
                placeholder="Password"
                aria-label="password"
                aria-describedby="basic-addon1"
                v-model="password"
              />
            </div>
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
              @click="addAccount"
            >
              confirm
            </button>
          </div>
        </div>
      </div>
      <div v-if="showEditAccount" class="modal-box" style="padding: 0">
        <div style="display: flex; flex-direction: column">
          <div class="modalHeader" style="display: flex; padding: 1rem">
            <span style="font-size: 1rem; font-weight: 600">Edit Account</span>
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
            <div class="modalBoxFormTitle">
            Current Email Address
            </div>
            <div class="input-group mb-3">
              <input
                type="email"
                class="form-control"
                placeholder="Enter New Email"
                aria-label="Email Address"
                aria-describedby="basic-addon1"
                v-model="email"
              />
            </div>
            <div class="modalBoxFormTitle">
            Current Role
            </div>
            <div class="input-group mb-3">
              <div class="dropdown">
                <input
                  type="button"
                  class="form-control"
                  :value="role || 'Select Role'"
                  @click="toggleRoleDropdown"
                />
                <div v-if="showRoleDropdown" class="dropdown-menu" @click.stop>
                  <p
                    v-for="roleOption in ['staff', 'system admin']"
                    :key="roleOption"
                    @click="selectRole(roleOption)"
                    class="dropdown-item"
                  >
                    {{ roleOption }}
                  </p>
                </div>
                <button class="delete-button" @click="deleteAccount">
                  Delete Account
                </button>
              </div>
            </div>
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
              @click="confirmAccount"
            >
              confirm
            </button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import x from "@/assets/x-lg.svg";
  import { supabase } from "@/client/supabase";

  export default {
    name: "accmanagement",
    data() {
      return {
        x,
        accountCount: [],
        showModal: false,
        showEditAccount: false,
        blur: false,
        showRoleDropdown: false,
        email: "",
        role: "",
        password: "",
        editingIndex: null,
      };
    },
    mounted() {
      this.getAccounts();
    },
    methods: {
      addAccountModal() {
        this.showModal = true;
        this.blur = true;
      },
      editAccount(index) {
        this.editingIndex = index;
        const account = this.accountCount[index];
        this.oldEmail = account.email;
        this.email = account.email;
        this.role = account.role;
        this.password = account.password;
        this.showEditAccount = true;
        this.blur = true;
      },
      closeModal() {
        this.showModal = false;
        this.blur = false;
        this.showEditAccount = false;
        this.oldEmail = "";
        this.email = "";
        this.role = "";
        this.password = "";
      },
      async confirmAccount() {
        if (this.editingIndex !== null) {
          const updatedAccount = {
            email: this.email,
            role: this.role,
            password: this.password,
          };
          this.accountCount[this.editingIndex] = updatedAccount;
          const { data, error } = await supabase
            .from("users")
            .update({ email: this.email, role: this.role })
            .eq("email", this.oldEmail);
        }
        this.closeModal();
      },
      async addAccount() {
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
        const { data, error } = await supabase
          .from("users")
          .insert({ email: this.email, role: this.role });

        this.accountCount.push({
          email: this.email,
          role: this.role,
          password: "hidden",
        });
        this.closeModal();
      },
      async deleteAccount() {
        if (this.editingIndex !== null) {
          const emailToDelete = this.oldEmail;

          // Delete from the database
          const { data, error } = await supabase
            .from("users")
            .delete()
            .eq("email", emailToDelete);

          if (error) {
            console.error("Error deleting account:", error);
            alert("Failed to delete account.");
            return;
          }

          // Remove from the local account list
          this.accountCount.splice(this.editingIndex, 1);
          alert("Account deleted successfully.");
        }

        // Close the modal
        this.closeModal();
      },
      toggleRoleDropdown() {
        this.showRoleDropdown = !this.showRoleDropdown;
      },

      selectRole(selectedRole) {
        this.role = selectedRole;
        this.showRoleDropdown = false;
      },
      closeDropdown() {
        this.showRoleDropdown = false;
      },
      async getAccounts() {
        const { data, error } = await supabase
          .from("users")
          .select("user_id, email, role");

        if (error) {
          console.error(error);
        }

        if (data) {
          const sortedData = data
            .filter((item) => item.role !== "super admin")
            .sort((a, b) => a.user_id - b.user_id);
          this.accountCount = sortedData.map((item) => ({
            email: item.email,
            role: item.role,
          }));
        }
      },
    },
  };
</script>

<style scoped>
  .delete-button {
    background: #ffffff;
    border: 1px solid #dc3545;
    color: #dc3545;
    border-radius: 5px;
    padding: 1rem;
    cursor: pointer;
    width: 100%;
    text-align: center;
  }
  .delete-button:hover {
    background: #ffcccc;
  }
  .accmanagement {
    background: #e9ecef;
    height: 83vh;
  }

  .container {
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 2rem;
    gap: 0;
  }

  .boxHeader {
    width: 69rem;
    height: 3.0625rem;
    background: #031633;
    display: flex;
  }

  .boxHeaderTexts {
    display: flex;
    justify-content: space-between;
    width: 100%;
  }

  .newAccount {
    width: 69rem;
    height: 3.0625rem;
    background: #031633;
    display: flex;
    justify-content: center;
  }

  .newAccountTexts  p{
    display: flex;
    width: 100%;
    color: white;
    font-weight: bold;
    margin: 0;
  }

  .boxHeaderTexts p {
    color: white;
    font-weight: bold;
    margin: 0;
    flex: 1;
  }

  .boxHeaderTexts,
  .ticketBox {
    display: flex;
    align-items: center;
    width: 100%;
    padding: 0 1rem;
  }

  .boxHeaderTexts p,
  .ticketBox p {
    margin: 0;
    text-align: center;
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }

  .boxHeaderTexts p:nth-child(1),
  .ticketBox p:nth-child(1) {
    flex: 1;
    text-align: left;
  }

  .boxHeaderTexts p:nth-child(2),
  .ticketBox p:nth-child(2) {
    flex: 3;
    text-align: left;
  }

  .boxHeaderTexts p:nth-child(3),
  .ticketBox p:nth-child(3) {
    flex: 2;
    text-align: left;
  }

  .boxHeaderTexts p:nth-child(4),
  .ticketBox p:nth-child(4) {
    flex: 2;
  }

  .boxHeaderTexts p:nth-child(5),
  .ticketBox .statusBox {
    flex: 2;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  .ticketBox {
    width: 69rem;
    height: 3rem;
    background: #ffffff;
    border-bottom: 1px solid #dee2e6;
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
    /* Ensure this is above other elements */
    display: block;
    /* Explicitly show the dropdown */
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
    z-index: 999;
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
    width: 80%;
    height: 100%;
    background: none;
    border: none;
    font-size: 0.9rem;
    cursor: pointer;
    border-radius: 10px;
    background-color: #ebe5fc;
    font-weight: 600;
  }

  .statusBox {
    position: relative;
    overflow: visible;
    height: 2rem;
    
   
    display: flex;
    align-items: center;
    justify-content: center;
  }
</style>
