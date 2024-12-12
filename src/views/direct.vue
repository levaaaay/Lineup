<template>
  <div class="direct"></div>
</template>

<script>
  import { supabase } from "../client/supabase";
  export default {
    name: "direct",
    async mounted() {
      const email = await this.getEmail();
      if (email) {
        this.homeDirectory(email);
      } else {
        console.error("No email found in the session.");
      }
    },
    methods: {
      async homeDirectory(email) {
        const { data, error } = await supabase
          .from("users")
          .select("role")
          .eq("email", email);
        if (data.length === 0) {
          this.$router.push("/");
        } else {
          if (data[0].role === "staff") {
            this.$router.push("staffhome");
          } else if (data[0].role === "system admin") {
            this.$router.push("sysadhome");
          }
        }
      },
      async getEmail() {
        const {
          data: { session },
          error,
        } = await supabase.auth.getSession();

        if (session) {
          return session.user.email;
        }
      },
    },
  };
</script>
